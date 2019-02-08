using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UdpLogger.Entities
{
    class LogEntry
    {
        public string LogLevel { get; set; }

        public string ThingName { get; set; }

        public DateTime Time { get; set; }

        public string Message { get; set; }

        public string Tag { get; set; }

        /// <summary>
        /// Constructor for LogEntry
        /// </summary>
        /// <param name="logLevel"></param>
        /// <param name="tag"></param>
        /// <param name="thingName"></param>
        /// <param name="message"></param>
        /// <param name="time"></param>
        public LogEntry(string logLevel, string tag, string thingName, string message, DateTime time)
        {
            LogLevel = logLevel ?? throw new ArgumentNullException(nameof(logLevel));
            Tag = tag ?? throw new ArgumentNullException(nameof(tag));
            ThingName = thingName ?? throw new ArgumentNullException(nameof(thingName));
            Message = message ?? throw new ArgumentNullException(nameof(message));
            Time = time;
        }

        public LogEntry()
        {
        }

        /// <summary>
        /// Override the ToString Method.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return LogLevel + ";" + Tag + ";" + ThingName + ";" + Message + ";" + Time.ToString();
        }
    }
}
