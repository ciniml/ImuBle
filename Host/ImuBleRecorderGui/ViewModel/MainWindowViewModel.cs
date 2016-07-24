using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using ImuBle.Device;
using ImuBle.Ui.Model;
using Livet.Behaviors.Messaging.IO;
using Livet.Messaging;
using Livet.Messaging.IO;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using Reactive.Bindings.Notifiers;

namespace ImuBle.Ui.ViewModel
{
    public class MainWindowViewModel : Livet.ViewModel
    {
        public static readonly string GenericErrorMessageKey = nameof(GenericErrorMessageKey);

        private readonly ImuEnumeratorService imuEnumerator;
        private readonly RecordingService recording;
        public ReadOnlyReactiveCollection<IImuDeviceId> Devices { get; }
        public ReactiveProperty<IImuDeviceId> SelectedDevice { get; }
        public ReactiveCommand ResetDeviceCommand { get; }

        public ReadOnlyReactiveProperty<bool> IsConnecting { get; }
        public ReadOnlyReactiveProperty<bool> IsConnected { get; }
        public ReactiveProperty<bool> IsRecording { get; }
        public ReadOnlyReactiveProperty<bool> CanRecord { get; }
        public ReadOnlyReactiveProperty<bool> CanChangeDevice { get; }

        [Required]
        public ReactiveProperty<string> OutputFilePath { get; }
        
        public ReadOnlyReactiveProperty<OxyPlot.PlotModel> PlotModel { get; }
        public ReactiveProperty<bool> AutoUpdatingPlot { get; }
        public ReactiveCommand<SavingFileSelectionMessage> ChangeOutputFilePathCommand { get; }

        public MainWindowViewModel()
        {
            this.imuEnumerator = ((App) Application.Current).ImuEnumerator;
            this.recording = ((App) Application.Current).Recording;

            this.IsConnecting = this.recording.IsConnecting.ObserveOnUIDispatcher().Do(value => LogEventSource.Log.Verbose($"IsConnecting={value}")).ToReadOnlyReactiveProperty().AddTo(this.CompositeDisposable);
            this.IsConnected = this.recording.IsConnected.ObserveOnUIDispatcher().Do(value => LogEventSource.Log.Verbose($"IsConnected={value}")).ToReadOnlyReactiveProperty().AddTo(this.CompositeDisposable);
            this.IsRecording = this.recording.IsRecording.ToReactivePropertyAsSynchronized(self => self.Value).AddTo(this.CompositeDisposable);

            this.CanChangeDevice = this.IsConnecting.Select(value => !value).ToReadOnlyReactiveProperty().AddTo(this.CompositeDisposable);

            this.OutputFilePath = this.recording.OutputFilePath
                .ToReactivePropertyAsSynchronized(self => self.Value)
                .AddTo(this.CompositeDisposable);
            this.OutputFilePath.SetValidateAttribute(() => this.OutputFilePath);
            this.ChangeOutputFilePathCommand = new ReactiveCommand<SavingFileSelectionMessage>().AddTo(this.CompositeDisposable);
            this.ChangeOutputFilePathCommand
                .Where(message => message.Response != null && message.Response.Any(path => !string.IsNullOrEmpty(path)))
                .Subscribe(message => this.OutputFilePath.Value = message.Response.First(path => !string.IsNullOrEmpty(path)))
                .AddTo(this.CompositeDisposable);

            this.CanRecord = Observable.CombineLatest(
                this.OutputFilePath.ObserveHasErrors,
                this.IsConnected,
                (hasErrors, isConnected) => !hasErrors && isConnected)
                .ToReadOnlyReactiveProperty()
                .AddTo(this.CompositeDisposable);

            this.Devices = this.imuEnumerator.Devices;
            this.SelectedDevice = new ReactiveProperty<IImuDeviceId>().AddTo(this.CompositeDisposable);
            this.SelectedDevice
                .Do(deviceInformation =>
                {
                    recording.TargetDevice.Value = deviceInformation;
                })
                .OnErrorRetry()
                .Subscribe()
                .AddTo(this.CompositeDisposable);

            this.ResetDeviceCommand = this.CanChangeDevice.ToReactiveCommand().AddTo(this.CompositeDisposable);
            this.ResetDeviceCommand
                .Subscribe(_ => this.recording.ResetDevice())
                .AddTo(this.CompositeDisposable);

            recording.ErrorOccured
                .Subscribe(errorMessage =>
                {
                    var message = new InformationMessage(errorMessage, "Error", MessageBoxImage.Error, GenericErrorMessageKey);
                    this.Messenger.Raise(message);
                })
                .AddTo(this.CompositeDisposable);
            

            var dataSeries = new []
            {
                CreateSeries("Acceleration(X)", "AccelerationAxis", item => item.Acceleration.X),
                CreateSeries("Acceleration(Y)", "AccelerationAxis", item => item.Acceleration.Y),
                CreateSeries("Acceleration(Z)", "AccelerationAxis", item => item.Acceleration.Z),
                CreateSeries("Acceleration Wide(X)", "AccelerationAxis", item => item.AccelerationWide.X),
                CreateSeries("Acceleration Wide(Y)", "AccelerationAxis", item => item.AccelerationWide.Y),
                CreateSeries("Acceleration Wide(Z)", "AccelerationAxis", item => item.AccelerationWide.Z),
                CreateSeries("Angular Velocity(X)", "AngularVelocityAxis", item => item.Rotation.X),
                CreateSeries("Angular Velocity(Y)", "AngularVelocityAxis", item => item.Rotation.Y),
                CreateSeries("Angular Velocity(Z)", "AngularVelocityAxis", item => item.Rotation.Z),
                CreateSeries("Magnetism(X)", "MagnetismAxis", item => item.Magnetism.X),
                CreateSeries("Magnetism(Y)", "MagnetismAxis", item => item.Magnetism.Y),
                CreateSeries("Magnetism(Z)", "MagnetismAxis", item => item.Magnetism.Z),
            };

            var plotModel = new PlotModel()
            {
                LegendPlacement = LegendPlacement.Outside
            };
            plotModel.Axes.Add(new DateTimeAxis()
            {
                Title="Time",
                Position = AxisPosition.Bottom,
                Key="TimeAxis",
                StringFormat = "T",
            });
            plotModel.Axes.Add(new LinearAxis()
            {
                Title = "Acceleration [mG]",
                Position = AxisPosition.Left,
                Key = "AccelerationAxis",
                StartPosition = 0.6,
                EndPosition = 0.85,
            });
            plotModel.Axes.Add(new LinearAxis()
            {
                Title = "Angular Velocity [mdps]",
                Position = AxisPosition.Left,
                Key = "AngularVelocityAxis",
                StartPosition = 0.3,
                EndPosition = 0.55,
            });
            plotModel.Axes.Add(new LinearAxis()
            {
                Title = "Magnetism [mgauss]",
                Position = AxisPosition.Left,
                Key = "MagnetismAxis",
                StartPosition = 0.0,
                EndPosition = 0.25,
            });
            foreach (var series in dataSeries)
            {
                plotModel.Series.Add(series);
            }
            
            this.PlotModel = Observable.Return(plotModel).ToReadOnlyReactiveProperty().AddTo(this.CompositeDisposable);

            this.AutoUpdatingPlot = new ReactiveProperty<bool>(true).AddTo(this.CompositeDisposable);
            this.recording.History
                .Where(_ => this.AutoUpdatingPlot.Value)
                .Subscribe(history =>
                {
                    foreach (var series in dataSeries)
                    {
                        series.Points.Clear();
                        var valueSelector = (Func<ImuDataReceivedEventArgs, float>) series.Tag;
                        var dataPoints = HistoryToDataPoint(history, valueSelector);
                        series.Points.AddRange(dataPoints);
                    }
                    
                    plotModel.InvalidatePlot(true);
                })
                .AddTo(this.CompositeDisposable);
        }

        private static LineSeries CreateSeries(string title, string yAxisKey, Func<ImuDataReceivedEventArgs, float> valueSelector)
        {
            return new LineSeries()
            {
                Title = title,
                XAxisKey = "TimeAxis",
                YAxisKey = yAxisKey,
                Tag = valueSelector,
            };
        }
        private static IEnumerable<DataPoint> HistoryToDataPoint(ImuDataReceivedEventArgs[] history, Func<ImuDataReceivedEventArgs, float> valueSelector)
        {
            return history.Select(item => new DataPoint(DateTimeAxis.ToDouble(item.Timestamp.LocalDateTime), valueSelector(item)));
        }
    }
}
