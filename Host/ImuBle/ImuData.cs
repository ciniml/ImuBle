using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImuBle
{
    /// <summary>
    /// A sample data from IMU device
    /// </summary>
    public class ImuData
    {
        /// <summary>
        /// Get acceleration data.
        /// </summary>
        public ImuVector3 Acceleration { get; }
        /// <summary>
        /// Get wide-range acceleration data.
        /// </summary>
        public ImuVector3 AccelerationWide { get; }
        /// <summary>
        /// Get angular velocity data.
        /// </summary>
        public ImuVector3 AngularVelocity { get; }
        /// <summary>
        /// Get magnetism data.
        /// </summary>
        public ImuVector3 Magnetism { get; }
        /// <summary>
        /// Get timestamp of data.
        /// </summary>
        public DateTimeOffset Timestamp { get; }

        public ImuData(DateTimeOffset timestamp, ImuVector3 acceleration, ImuVector3 accelerationWide, ImuVector3 angularVelocity, ImuVector3 magnetism)
        {
            this.Timestamp = timestamp;
            this.Acceleration = acceleration;
            this.AccelerationWide = accelerationWide;
            this.AngularVelocity = angularVelocity;
            this.Magnetism = magnetism;
        }
    }
}
