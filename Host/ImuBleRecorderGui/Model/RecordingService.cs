﻿using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reactive;
using System.Reactive.Disposables;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using Reactive.Bindings.Notifiers;

namespace ImuBle.Ui.Model
{
    public class RecordingService : IDisposable
    {
        public ReactiveProperty<ImuBleDeviceInformation> TargetDevice { get; }
        public ReactiveProperty<string> OutputFilePath { get; }
        public ReadOnlyReactiveProperty<bool> IsConnecting { get; }
        public ReadOnlyReactiveProperty<bool> IsConnected { get; }
        public ReactiveProperty<bool> IsRecording { get; }

        private readonly Subject<string> errorOccuredSubject;
        public IObservable<string> ErrorOccured => this.errorOccuredSubject.AsObservable();

        private readonly Subject<Unit> deviceChangedSubject;
        public IObservable<Unit> DeviceChanged => this.deviceChangedSubject.AsObservable();
        public IObservable<ImuDataReceivedEventArgs> DataReceived { get; }


        private readonly Queue<ImuDataReceivedEventArgs> historyQueue = new Queue<ImuDataReceivedEventArgs>();
        public IObservable<ImuDataReceivedEventArgs[]> History { get; }
        public ReactiveProperty<TimeSpan> HistoryDuration { get; }
        public ReactiveProperty<TimeSpan> HistoryUpdateInterval { get; }

        private readonly CompositeDisposable disposables = new CompositeDisposable();
        private ImuBleDevice device;

        public RecordingService()
        {
            this.errorOccuredSubject = new Subject<string>();

            var connectingNotifier = new BusyNotifier();
            var isConnected = new ReactiveProperty<bool>();
            this.IsConnecting = connectingNotifier.ToReadOnlyReactiveProperty().AddTo(this.disposables);
            this.IsConnected = isConnected.ToReadOnlyReactiveProperty().AddTo(this.disposables);

            this.deviceChangedSubject = new Subject<Unit>();
            this.TargetDevice = new ReactiveProperty<ImuBleDeviceInformation>().AddTo(this.disposables);
            var dataReceivedObservable = this.TargetDevice
                .Where(deviceInformation => deviceInformation != null && !connectingNotifier.IsBusy && !this.IsRecording.Value)
                .Select(deviceInformation =>
                {
                    isConnected.Value = false;
                    this.device = null;
                    return Observable.FromAsync(async (cancellationToken) =>
                    {
                        using (connectingNotifier.ProcessStart())
                        {
                            this.device = await ImuBleDevice.CreateFromId(deviceInformation.Id, cancellationToken);
                            await this.device.EnableNotifications(cancellationToken);
                            await this.device.SetInterval(10, cancellationToken);
                            this.deviceChangedSubject.OnNext(Unit.Default);
                        }
                        isConnected.Value = true;
                        return Observable.FromEventPattern<ImuDataReceivedEventArgs>(
                            handler => this.device.DataReceived += handler,
                            handler => this.device.DataReceived -= handler);
                    });
                })
                .Switch()
                .OnErrorRetry((Exception e) => this.errorOccuredSubject.OnNext(e.Message))
                .Switch()
                .Select(eventPack => eventPack.EventArgs)
                .Publish();

            this.DataReceived = dataReceivedObservable.AsObservable();
            this.IsRecording = new ReactiveProperty<bool>().AddTo(this.disposables);
            this.OutputFilePath = new ReactiveProperty<string>().AddTo(this.disposables);
            this.HistoryDuration = new ReactiveProperty<TimeSpan>(TimeSpan.FromSeconds(60)).AddTo(this.disposables);
            this.HistoryUpdateInterval = new ReactiveProperty<TimeSpan>(TimeSpan.FromMilliseconds(100)).AddTo(this.disposables);

            Observable.CombineLatest(
                this.OutputFilePath,
                this.IsRecording.Where(value => value),
                (outputFilePath, _) => outputFilePath)
                .Select(outputFilePath =>
                {
                    var task = new RecordingTask(dataReceivedObservable, outputFilePath);
                    return this.IsRecording.Where(value => !value).Take(1).Finally(() => task.Dispose());
                })
                .Switch()
                .OnErrorRetry()
                .Subscribe()
                .AddTo(this.disposables);

            this.History = this.HistoryUpdateInterval
                .Select(updateInterval => 
                    dataReceivedObservable
                    .Select(eventArgs =>
                    {
                        this.historyQueue.Enqueue(eventArgs);
                        var oldestTimestamp = DateTimeOffset.Now - this.HistoryDuration.Value;
                        lock (this.historyQueue)
                        {
                            while (this.historyQueue.Count > 0)
                            {
                                var data = this.historyQueue.Peek();

                                if (data.Timestamp < oldestTimestamp)
                                {
                                    this.historyQueue.Dequeue();
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        return Unit.Default;
                    })
                    .Buffer(updateInterval)
                    .Select(_ =>
                    {
                        lock (this.historyQueue)
                        {
                            return this.historyQueue.ToArray();
                        }
                    })
                 )
                 .Switch()
                .AsObservable();
                
            dataReceivedObservable.Connect().AddTo(this.disposables);
        }
        
        public void Dispose()
        {
            this.disposables.Dispose();
        }
    }

    internal class RecordingTask : IDisposable
    {
        public string OutputPath { get; }
        private readonly StreamWriter writer;
        private readonly CompositeDisposable disposables = new CompositeDisposable();

        private int sampleNumber = 0;
        private void WriteVector3(ImuVector3 vector3) => writer.Write($",{vector3.X},{vector3.Y},{vector3.Z}");

        public RecordingTask(IObservable<ImuDataReceivedEventArgs> dataReceivedObservable, string outputPath)
        {
            if( dataReceivedObservable == null ) throw new ArgumentNullException(nameof(dataReceivedObservable));
            if( string.IsNullOrEmpty(outputPath) ) throw new ArgumentException("outputPath must not be null or empty.", nameof(outputPath));

            this.OutputPath = outputPath;
            this.writer = new StreamWriter(new FileStream(this.OutputPath, FileMode.Create, FileAccess.Write, FileShare.Read), Encoding.UTF8).AddTo(this.disposables);
            dataReceivedObservable
                .Do(eventArgs =>
                {
                    this.writer.Write(this.sampleNumber++);
                    this.WriteVector3(eventArgs.Rotation);
                    this.WriteVector3(eventArgs.Acceleration);
                    this.WriteVector3(eventArgs.AccelerationWide);
                    this.WriteVector3(eventArgs.Magnetism);
                    this.writer.WriteLine();
                })
                .OnErrorRetry()
                .Subscribe()
                .AddTo(this.disposables);
        }

        public void Dispose()
        {
            this.disposables.Dispose();
        }
    }
}
