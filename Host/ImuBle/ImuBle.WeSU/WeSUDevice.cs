using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using WindowsBlueSt;
using WindowsBlueSt.WeSU;

namespace ImuBle.WeSU
{
    // ReSharper disable once InconsistentNaming
    public class WeSUDeviceId : IImuDeviceId
    {
        internal BlueStDeviceInformation BlueStDeviceInformation { get; }

        public Guid Id => this.BlueStDeviceInformation.Id;
        public string Name => $"WeSU({this.BlueStDeviceInformation.Id.ToString()})";
        
        internal WeSUDeviceId(BlueStDeviceInformation blueStDeviceInformation)
        {
            this.BlueStDeviceInformation = blueStDeviceInformation;
        }
    }

    // ReSharper disable once InconsistentNaming
    public class WeSUDevice : IImuDevice
    {
        private const BlueStFeatureMask AggregateFeatureMask = BlueStFeatureMask.Acc | BlueStFeatureMask.Gyro | BlueStFeatureMask.Mag;

        private readonly BlueStDevice blueStDevice;
        public event EventHandler<ImuDataReceivedEventArgs> DataReceived;

        private static ImuVector3 ToImuVector3(BlueStMotionSensorFeatureData data)
        {
            return new ImuVector3() {X = data.X, Y = data.Y, Z = data.Z};
        }

        public static async Task<WeSUDeviceId[]> FindAllDeviceAsync(CancellationToken cancellationToken)
        {
            var devices = await BlueSt.FindAllBlueStDevices(cancellationToken);
            return devices.Select(device => new WeSUDeviceId(device)).ToArray();
        }

        public static async Task<WeSUDevice> CreateFromIdAsync(WeSUDeviceId deviceId, CancellationToken cancellationToken)
        {
            var deviceInformation = deviceId.BlueStDeviceInformation;

            var aggregateFeatures = new[]
            {
                AggregateFeatureMask
            };

            var blueStDevice = await BlueStDevice.CreateFromId(deviceInformation.Id, aggregateFeatures, cancellationToken);
            await blueStDevice.DisableAllFeatureDataNotifications();

            {
                var config = new WeSUConfig();
                await config.LoadRegistersAsync(blueStDevice, cancellationToken);
                
                // Configure registers
                config.AccelerometerFullScale = 16;
                config.AccelerometerOutputDataRate = 208;
                config.GyroFullScale = 2000;
                config.GyroOutputDataRate = 208;
                config.MagnetometerFullScale = 12;
                config.MagnetometerOutputDataRate = 80;
                config.TimerFrequency = 133;

                await config.SaveRegistersAsync(blueStDevice, cancellationToken);
            }

            var wesuDevice = new WeSUDevice(blueStDevice);
            return wesuDevice;
        }

        private WeSUDevice(BlueStDevice blueStDevice)
        {
            this.blueStDevice = blueStDevice;
            this.blueStDevice.FeatureDataReceived += (sender, eventArgs) =>
            {
                if (eventArgs.Data.Features == (BlueStFeatureMask.Acc | BlueStFeatureMask.Gyro | BlueStFeatureMask.Mag))
                {
                    // Accelerometer single feature
                    var stream = eventArgs.Data.Data;

                    var motion = new BlueStAggregateFeatureData(() => new IFeatureData[]
                    {
                        new BlueStMotionSensorFeatureData(),
                        new BlueStMotionSensorFeatureData(),
                        new BlueStMotionSensorFeatureData(),
                    });
                    motion.Decode(stream);
                    var motionData = motion.FeatureData.Cast<BlueStMotionSensorFeatureData>().ToArray();
                    var acceleration = ToImuVector3(motionData[0]);
                    var angularVelocity = ToImuVector3(motionData[1]);
                    var magnetism = ToImuVector3(motionData[2]);
                    var imuData = new ImuData(DateTimeOffset.Now, acceleration, new ImuVector3(), angularVelocity, magnetism);

                    this.DataReceived?.Invoke(this, new ImuDataReceivedEventArgs(imuData));
                }
            };
        }

        public Task SetIntervalAsync(int intervalMilliseconds, CancellationToken cancellationToken)
        {
            return Task.FromResult(0);
        }

        public Task<ImuData[]> ReadAggregateValuesAsync(CancellationToken cancellationToken)
        {
            return Task.FromResult(new ImuData[0]);
        }

        public Task EnableNotificationsAsync(CancellationToken cancellationToken)
        {
            return this.blueStDevice.EnableFeatureDataNotification(AggregateFeatureMask);
        }

        public Task DisableNotificationsAsync(CancellationToken cancellationToken)
        {
            return this.blueStDevice.DisableAllFeatureDataNotifications();
        }
    }
}
