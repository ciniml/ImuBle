using System;
using System.Threading;
using System.Threading.Tasks;

namespace ImuBle
{
    public interface IImuDevice
    {
        event EventHandler<ImuDataReceivedEventArgs> DataReceived;

        Task DisableNotificationsAsync(CancellationToken cancellationToken);
        Task EnableNotificationsAsync(CancellationToken cancellationToken);
        Task<ImuData[]> ReadAggregateValuesAsync(CancellationToken cancellationToken);
        Task SetIntervalAsync(int intervalMilliseconds, CancellationToken cancellationToken);
    }
}