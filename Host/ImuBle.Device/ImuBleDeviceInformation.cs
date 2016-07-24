using System;

namespace ImuBle.Device
{
    public class ImuBleDeviceInformation : IImuDeviceId
    {
        public Guid Id { get; }
        public string Name => $"IMUBLE({this.Id.ToString()})";

        internal ImuBleDeviceInformation(Guid id)
        {
            this.Id = id;
        }
    }
}