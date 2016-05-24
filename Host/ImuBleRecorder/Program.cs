using System;
using System.Collections.Concurrent;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Markup;
using ImuBle;

namespace ImuBleRecorder
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Press [ENTER] to exit.");

            using (var cancelSource = new CancellationTokenSource())
            {
                var task = MainAsyncOuter(args, cancelSource.Token);
                Console.ReadLine();
                cancelSource.Cancel();
                Console.WriteLine("Waiting util the main task finishes.");
                task.Wait();
            }
        }

        static async Task MainAsyncOuter(string[] args, CancellationToken cancellationToken)
        {
            try
            {
                await MainAsync(args, cancellationToken);
            }
            catch (AggregateException e) when (e.Flatten().InnerExceptions.SingleOrDefault() is OperationCanceledException)
            {
            }
            catch (OperationCanceledException)
            {
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e.ToString());
            }
        }

        static async Task MainAsync(string[] args, CancellationToken cancellationToken)
        {
            Console.WriteLine("Finding IMUBLE devices...");
            var deviceInformations = await ImuBleDevice.FindAllDevices(cancellationToken);

            if (deviceInformations.Length == 0)
            {
                Console.WriteLine("No IMUBLE devices found. Please check connection status of device.");
                return;
            }
            if (deviceInformations.Length > 1)
            {
                Console.WriteLine("Two or more IMUBLE devices are found. Force to use the first one.");
            }
            var deviceInformation = deviceInformations.First();

            

            var imuBleDevice = await ImuBleDevice.CreateFromId(deviceInformation.Id, cancellationToken);
            Console.WriteLine("Paired device was found. Trying to connect to this device...");
            await imuBleDevice.DisableNotifications(cancellationToken);

            Console.WriteLine("Connected to device successfully.");
            
            var dataQueue = new ConcurrentQueue<ImuDataReceivedEventArgs>();
            
            imuBleDevice.DataReceived += (sender, eventArgs) =>
            {
                if (cancellationToken.IsCancellationRequested) return;  // If cancelled, do nothing.
                dataQueue.Enqueue(eventArgs);
            };

            {
                var values = await imuBleDevice.ReadAggregateValues(cancellationToken);
                foreach (var value in values)
                {
                    Console.WriteLine($"Acceleration = {value.Acceleration.X},{value.Acceleration.Y},{value.Acceleration.Z}");
                }
            }

            Console.WriteLine("Configuring sampling interval to 5[ms].");
            // Set interval to 5[ms]
            await imuBleDevice.SetInterval(5, cancellationToken);

            Console.WriteLine("Enable notifications for all features.");
            await imuBleDevice.EnableNotifications(cancellationToken);

            Console.WriteLine("Waiting first data arrives from the device...");

            var firstDataArrived = false;

            // Write received data.
            var writeoutTask = Task.Run(async () =>
            {
                int sampleNumber = 0;
                Action<StreamWriter, ImuVector3> writeVector3 = (writer, vector3) => writer.Write($",{vector3.X},{vector3.Y},{vector3.Z}");

                using(var stream = new FileStream("output.csv", FileMode.Create, FileAccess.Write, FileShare.None, 4096))
                using (var writer = new StreamWriter(stream, Encoding.UTF8, 4096, true))
                {
                    while (!(dataQueue.IsEmpty && cancellationToken.IsCancellationRequested))
                    {
                        ImuDataReceivedEventArgs data;
                        if (dataQueue.TryDequeue(out data))
                        {
                            if (!firstDataArrived)
                            {
                                Console.WriteLine("First data received.");
                                firstDataArrived = true;
                            }
                            writer.Write(sampleNumber++);
                            writeVector3(writer, data.Rotation);
                            writeVector3(writer, data.Acceleration);
                            writeVector3(writer, data.AccelerationWide);
                            writeVector3(writer, data.Magnetism);
                            writer.WriteLine();
                        }
                        else
                        {
                            try
                            {
                                await Task.Delay(1, cancellationToken);
                            }
                            catch (OperationCanceledException)
                            {
                            }
                        }
                    }

                }
            }, cancellationToken);

            await writeoutTask;
            // Disable all notifications before disconnecting from the peripheral.
            await imuBleDevice.DisableNotifications(cancellationToken);
        }
    }
}
