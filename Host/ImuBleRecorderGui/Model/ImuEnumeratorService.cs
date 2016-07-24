using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reactive;
using System.Reactive.Disposables;
using System.Reactive.Linq;
using System.Reactive.Subjects;
using System.Reactive.Threading.Tasks;
using System.Text;
using System.Threading.Tasks;
using ImuBle.Device;
using ImuBle.WeSU;
using Reactive.Bindings;
using Reactive.Bindings.Extensions;
using Reactive.Bindings.Notifiers;

namespace ImuBle.Ui.Model
{
    public class ImuEnumeratorService : IDisposable
    {
        private readonly ReactiveCollection<IImuDeviceId> devices = new ReactiveCollection<IImuDeviceId>();
        private readonly Subject<Unit> enumerateSubject = new Subject<Unit>();
        private readonly CompositeDisposable disposables = new CompositeDisposable();

        public ReadOnlyReactiveProperty<bool> IsEnumerating { get; }

        public ReadOnlyReactiveCollection<IImuDeviceId> Devices { get; }

        public ImuEnumeratorService()
        {
            this.Devices = this.devices.ToReadOnlyReactiveCollection();

            var isEnumerating = new ReactiveProperty<bool>();
            this.IsEnumerating = isEnumerating.ToReadOnlyReactiveProperty();

            var imuBleDevicesObservable = Observable.FromAsync(cancellationToken => ImuBleDevice.FindAllDevices(cancellationToken)).Select(devices => devices.Cast<IImuDeviceId>());
            var wesuDeviceObservable = Observable.FromAsync(cancellationToken => WeSUDevice.FindAllDeviceAsync(cancellationToken)).Select(devices => devices.Cast<IImuDeviceId>());
            this.enumerateSubject
                .Where(_ => !isEnumerating.Value)
                .Do(_ =>
                {
                    isEnumerating.Value = true;
                    this.devices.Clear();
                })
                .SelectMany(_ => imuBleDevicesObservable.Merge(wesuDeviceObservable))
                .Do(devices =>
                {
                    foreach (var device in devices)
                    {
                        this.devices.Add(device);
                    }
                })
                .Do(_ => isEnumerating.Value = false)
                .Subscribe()
                .AddTo(this.disposables);

            this.Enumerate();
        }

        public void Enumerate()
        {
            this.enumerateSubject.OnNext(Unit.Default);
        }

        public void Dispose()
        {
            this.disposables.Dispose();
        }
    }
}
