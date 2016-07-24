using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;

namespace ImuBle
{
    /// <summary>
    /// BLE communication utility
    /// </summary>
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
}
