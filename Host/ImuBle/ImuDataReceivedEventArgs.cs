using System;

namespace ImuBle
{
    public class ImuDataReceivedEventArgs : EventArgs
    {
        public ImuData Data { get; }

        public ImuVector3 Acceleration => this.Data.Acceleration;
        public ImuVector3 AccelerationWide => this.Data.AccelerationWide;
        public ImuVector3 Rotation => this.Data.AngularVelocity;
        public ImuVector3 Magnetism => this.Data.Magnetism;
        public DateTimeOffset Timestamp => this.Data.Timestamp;

        public ImuDataReceivedEventArgs(ImuData data)
        {
            this.Data = data;
        }
        public ImuDataReceivedEventArgs(DateTimeOffset timestamp, ImuVector3 acceleration, ImuVector3 accelerationWide, ImuVector3 rotation, ImuVector3 magnetism)
            : this(new ImuData(timestamp, acceleration, accelerationWide, rotation, magnetism))
        {
        }
    }
}