using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

namespace ImuBle
{
    public interface IImuDeviceId
    {
        Guid Id { get; }
        string Name { get; }
    }
}
