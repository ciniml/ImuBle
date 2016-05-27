using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

namespace ImuBle
{
    public static class BleUtil
    {
        public static readonly string BluetoothGattDeviceServiceInterfaceClassGuid = "{6E3BB679-4372-40C8-9EAA-4509DF260CD8}";
        private const string ContainerIdProperty = "System.Devices.ContainerId";
        private const string InterfaceClassGuidProperty = "System.Devices.InterfaceClassGuid";
        private const string ServiceGuidProperty = "System.DeviceInterface.Bluetooth.ServiceGuid";
        private const string InterfaceEnabledProperty = "System.Devices.InterfaceEnabled";
        private const string AqsBooleanFalse = "System.StructuredQueryType.Boolean#False";
        private const string AqsBooleanTrue = "System.StructuredQueryType.Boolean#True";

        public static string GetDeviceSelecorEndsWithGuid(string guidPattern)
        {
            return $"{InterfaceClassGuidProperty}:={BluetoothGattDeviceServiceInterfaceClassGuid} AND {InterfaceEnabledProperty}:={AqsBooleanTrue} AND {ServiceGuidProperty}:~>\"{guidPattern}}}\"";
        }

        public static string AppendContainerIdCriterion(string aqsString, Guid containerId)
        {
            return $"{aqsString} AND {ContainerIdProperty}:=\"{{{containerId}}}\"";
        }

        public static async Task<IEnumerable<IGrouping<Guid, DeviceInformation>>> FindAllDeviceServicesAsync(string aqsFilter, CancellationToken cancellationToken)
        {
            return (await DeviceInformation.FindAllAsync(aqsFilter, new[] { ContainerIdProperty }).AsTask(cancellationToken)).GroupByDevice();
        }

        public static IEnumerable<IGrouping<Guid, DeviceInformation>> GroupByDevice(this IEnumerable<DeviceInformation> devices)
        {
            return devices.GroupBy(device => (Guid)device.Properties[ContainerIdProperty]);
        }
    }
    
    public struct ImuVector3
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
    }

    public class ImuDataReceivedEventArgs : EventArgs
    {
        public ImuVector3 Acceleration { get; }
        public ImuVector3 AccelerationWide { get; }
        public ImuVector3 Rotation { get; }
        public ImuVector3 Magnetism { get; }
        public DateTimeOffset Timestamp { get; }
        
        public ImuDataReceivedEventArgs(DateTimeOffset timestamp, ImuVector3 acceleration, ImuVector3 accelerationWide, ImuVector3 rotation, ImuVector3 magnetism)
        {
            this.Timestamp = timestamp;
            this.Acceleration = acceleration;
            this.AccelerationWide = accelerationWide;
            this.Rotation = rotation;
            this.Magnetism = magnetism;
        }
    }
    
    public class ImuBleDeviceInformation
    {
        public Guid Id { get; }

        internal ImuBleDeviceInformation(Guid id)
        {
            this.Id = id;
        }
    }
    
    public class ImuBleDevice
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
                this.DataReceived?.Invoke(this, value);
            }
        }

        private static ImuDataReceivedEventArgs[] ReadAggregateValues(IBuffer buffer, DateTimeOffset timestamp)
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
                    new ImuDataReceivedEventArgs(timestamp, acceleration1, accelerationWide1, rotation, magnetism),
                    new ImuDataReceivedEventArgs(timestamp, acceleration0, accelerationWide0, rotation, magnetism),
                };
            }
            else
            {
                return new ImuDataReceivedEventArgs[0];
            }
        }


        public async Task<ImuDataReceivedEventArgs[]> ReadAggregateValues(CancellationToken cancellationToken)
        {
            var result = await this.aggergatedCharacteristic.ReadValueAsync(BluetoothCacheMode.Uncached).AsTask(cancellationToken);
            if( result.Status == GattCommunicationStatus.Unreachable ) throw new InvalidOperationException("Failed to read aggregate values.");
            return ReadAggregateValues(result.Value, DateTimeOffset.Now);
        }
        public async Task SetInterval(int intervalMilliseconds, CancellationToken cancellationToken)
        {
            var data = BitConverter.GetBytes((ushort)intervalMilliseconds);
            var buffer = data.AsBuffer();
            await this.updateIntervalCharacteristic.WriteValueAsync(buffer).AsTask(cancellationToken);
        }

        public async Task DisableNotifications(CancellationToken cancellationToken)
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

        public async Task EnableNotifications(CancellationToken cancellationToken)
        {
            while (!cancellationToken.IsCancellationRequested)
            {
                try
                {
                    var newCccd = GattClientCharacteristicConfigurationDescriptorValue.Notify;
                    var result = await this.aggergatedCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(newCccd).AsTask(cancellationToken);
                    if (result == GattCommunicationStatus.Unreachable) throw new InvalidOperationException("Failed to set CCCD");

                    // Confirm the CCCD value.
                    {
                        var cccd = await this.aggergatedCharacteristic.ReadClientCharacteristicConfigurationDescriptorAsync().AsTask(cancellationToken);
                        if (cccd.ClientCharacteristicConfigurationDescriptor != GattClientCharacteristicConfigurationDescriptorValue.Notify)
                        {
                            continue;
                        }
                    }
                    return;
                }
                catch (Exception e) when ((uint) e.HResult == 0x8007001fu)
                {
                }
            }
        }

    }
}
