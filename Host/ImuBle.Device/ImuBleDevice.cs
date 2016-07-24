using System;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

namespace ImuBle.Device
{
    public class ImuBleDevice : IImuDevice
    {
        private static readonly Guid ImuServiceGuid = Guid.Parse("00010000-1000-2000-4012-3456789ab000");
        private static readonly Guid AggregatedCharacteristicGuid = Guid.Parse("00010000-1000-2000-4012-3456789ab001");
        private static readonly Guid UpdateIntervalGuid = Guid.Parse("00010000-1000-2000-4012-3456789ab002");

        public static async Task<ImuBleDeviceInformation[]> FindAllDevices(CancellationToken cancellationToken)
        {
            var selector = GattDeviceService.GetDeviceSelectorFromUuid(ImuServiceGuid);
            var deviceInformations = await BleUtil.FindAllDeviceServicesAsync(selector, cancellationToken);
            return deviceInformations.Select(deviceInformation => new ImuBleDeviceInformation(deviceInformation.Key)).ToArray();
        }

        private readonly Guid deviceId;
        private readonly GattDeviceService imuService;
        private readonly GattCharacteristic aggergatedCharacteristic;
        private readonly GattCharacteristic updateIntervalCharacteristic;

        public event EventHandler<ImuDataReceivedEventArgs> DataReceived;

        public static async Task<ImuBleDevice> CreateFromId(Guid deviceId, CancellationToken cancellationToken)
        {
            var serviceSelector = BleUtil.AppendContainerIdCriterion(GattDeviceService.GetDeviceSelectorFromUuid(ImuServiceGuid), deviceId);
            var serviceDeviceInformations = await DeviceInformation.FindAllAsync(serviceSelector).AsTask(cancellationToken);
            var imuServiceInformation = serviceDeviceInformations.Single();
            var imuService = await GattDeviceService.FromIdAsync(imuServiceInformation.Id).AsTask(cancellationToken);

            return new ImuBleDevice(deviceId, imuService);
        }
        
        internal ImuBleDevice(Guid deviceId, GattDeviceService imuService)
        {
            this.deviceId = deviceId;
            this.imuService = imuService;

            this.aggergatedCharacteristic = this.imuService.GetCharacteristics(AggregatedCharacteristicGuid).Single();
            this.updateIntervalCharacteristic = this.imuService.GetCharacteristics(UpdateIntervalGuid).Single();

            this.aggergatedCharacteristic.ValueChanged += (sender, args) => this.OnFeatureDataReceived(args);
        }

        private static ImuVector3 ReadVector3FromBuffer(byte[] buffer, int offset, float sensitivity)
        {
            var vector = new ImuVector3
            {
                X = BitConverter.ToInt16(buffer, offset + 0)*sensitivity,
                Y = BitConverter.ToInt16(buffer, offset + 2)*sensitivity,
                Z = BitConverter.ToInt16(buffer, offset + 4)*sensitivity
            };
            return vector;
        }

        private void OnFeatureDataReceived(GattValueChangedEventArgs e)
        {

            var values = ReadAggregateValues(e.CharacteristicValue, e.Timestamp);
            foreach (var value in values)
            {
                this.DataReceived?.Invoke(this, new ImuDataReceivedEventArgs(value));
            }
        }

        private static ImuData[] ReadAggregateValues(IBuffer buffer, DateTimeOffset timestamp)
        {
            const float accelerationSensitivity = 0.732f;
            const float accelerationWideSensitivity = 49f;
            const float rotationSensitivity = 70.0f;
            const float magneticSensitivity = 0.48f;

            var data = buffer.ToArray();
            if (data.Length >= 37)
            {
                var flags = data[0];
                var rotation = ReadVector3FromBuffer(data, 1, rotationSensitivity);
                var magnetism = ReadVector3FromBuffer(data, 7, magneticSensitivity);
                var acceleration0 = ReadVector3FromBuffer(data, 13, accelerationSensitivity);
                var acceleration1 = ReadVector3FromBuffer(data, 19, accelerationSensitivity);
                var accelerationWide0 = ReadVector3FromBuffer(data, 25, accelerationWideSensitivity);
                var accelerationWide1 = ReadVector3FromBuffer(data, 31, accelerationWideSensitivity);

                return new[]
                {
                    new ImuData(timestamp, acceleration1, accelerationWide1, rotation, magnetism),
                    new ImuData(timestamp, acceleration0, accelerationWide0, rotation, magnetism),
                };
            }
            else
            {
                return new ImuData[0];
            }
        }


        public async Task<ImuData[]> ReadAggregateValuesAsync(CancellationToken cancellationToken)
        {
            var result = await this.aggergatedCharacteristic.ReadValueAsync(BluetoothCacheMode.Uncached).AsTask(cancellationToken);
            if( result.Status == GattCommunicationStatus.Unreachable ) throw new InvalidOperationException("Failed to read aggregate values.");
            return ReadAggregateValues(result.Value, DateTimeOffset.Now);
        }
        public async Task SetIntervalAsync(int intervalMilliseconds, CancellationToken cancellationToken)
        {
            var data = BitConverter.GetBytes((ushort)intervalMilliseconds);
            var buffer = data.AsBuffer();
            await this.updateIntervalCharacteristic.WriteValueAsync(buffer).AsTask(cancellationToken);
        }

        public async Task DisableNotificationsAsync(CancellationToken cancellationToken)
        {
            try
            {
                var newCccd = GattClientCharacteristicConfigurationDescriptorValue.None;
                var result = await this.aggergatedCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(newCccd).AsTask(cancellationToken);
                if (result == GattCommunicationStatus.Unreachable) throw new InvalidOperationException("Failed to set CCCD");
            }
            catch (Exception e) when ((uint)e.HResult == 0x8007001fu)
            {
            }
        }

        public async Task EnableNotificationsAsync(CancellationToken cancellationToken)
        {
            while (!cancellationToken.IsCancellationRequested)
            {
                try
                {
                    var newCccd = GattClientCharacteristicConfigurationDescriptorValue.Notify;
                    var result = await this.aggergatedCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(newCccd).AsTask(cancellationToken);
                    if (result == GattCommunicationStatus.Unreachable) throw new InvalidOperationException("Failed to set CCCD");

                    //// Confirm the CCCD value.
                    //{
                    //    var cccd = await this.aggergatedCharacteristic.ReadClientCharacteristicConfigurationDescriptorAsync().AsTask(cancellationToken);
                    //    if (cccd.ClientCharacteristicConfigurationDescriptor != GattClientCharacteristicConfigurationDescriptorValue.Notify)
                    //    {
                    //        continue;
                    //    }
                    //}
                    return;
                }   
                catch (Exception e) when ((uint) e.HResult == 0x8007001fu)
                {
                }
            }
        }

    }
}