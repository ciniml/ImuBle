using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ImuBle.Ui.Model
{
    [EventSource(Guid="4F4C9637-9975-4E32-B039-20AF9870304C")]
    public class LogEventSource : EventSource
    {
        public static LogEventSource Log { get; } = new LogEventSource();

        [Event(1, Level=EventLevel.Informational)]
        public void Information(string message)
        {
            this.WriteEvent(1, message);
        }

        [Event(2, Level = EventLevel.Error)]
        public void Error(string message)
        {
            this.WriteEvent(2, message);
        }

        [Event(3, Level = EventLevel.Warning)]
        public void Warning(string message)
        {
            this.WriteEvent(3, message);
        }

        [Event(4, Level = EventLevel.Verbose)]
        public void Verbose(string message)
        {
            this.WriteEvent(4, message);
        }
    }
}
