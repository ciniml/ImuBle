using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ImuBle.Device;
using ImuBle.WeSU;

namespace ImuBle.Ui.Model
{
    public class ImuDeviceFactory
    {
        public static ImuDeviceFactory Default { get; } = new ImuDeviceFactory();

        public async Task<IImuDevice> CreateFromIdAsync(IImuDeviceId deviceId, CancellationToken cancellationToken)
        {
            var wesuDeviceId = deviceId as WeSUDeviceId;
            if (wesuDeviceId != null)
            {
                return await WeSUDevice.CreateFromIdAsync(wesuDeviceId, cancellationToken);
            }

            var imuBleDeviceId = deviceId as ImuBleDeviceInformation;
            if (imuBleDeviceId != null)
            {
                return await ImuBleDevice.CreateFromId(imuBleDeviceId.Id, cancellationToken);
            }

            throw new ArgumentException("Invalid device ID");
        }
    }
}
