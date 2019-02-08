using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace UdpLogger.Entities
{
    class LogUdpClient
    {
        private UdpClient UdpClient { get; set; }

        private IPEndPoint IpEndPoint { get; set; }

        public ObservableCollection<LogEntry> LogEntries { get; set; }

        public ObservableCollection<string> LogText { get; set; }

        public bool Save { get; set; }

        public string Path { get; set; }

        public int Port { get; set; }

        private List<LogEntry> WriteLogEntries { get; set; }

        /// <summary>
        /// Constructor initialise LogEntries, WriteLogEntries
        /// and starts the Task for writting the LogEntries
        /// </summary>
        public LogUdpClient()
        {
            LogEntries = new ObservableCollection<LogEntry>();
            WriteLogEntries = new List<LogEntry>();
            LogText = new ObservableCollection<string>();
            Task.Run (() => WriteData());
        }

        /// <summary>
        /// Read Async the Data from Udp.
        /// Added the data to the Observable List.
        /// </summary>
        /// <param name="asyncResult"></param>
        private void ReadUdpData(IAsyncResult asyncResult)
        {
            IPEndPoint endPoint = IpEndPoint;
            try
            {
                while (true)
                {
                    byte[] pdata = UdpClient.Receive(ref endPoint);
                    string logText = Encoding.ASCII.GetString(pdata);
                    Application.Current.Dispatcher.Invoke(() => LogText.Insert(0, logText));
                    string[] split = logText.Split(';');
                    if (split.Length >= 5)
                    {
                        LogEntry logEntry = new LogEntry(split[2], split[3], split[1], split[4].Replace('\n', ' ').Replace('\r', ' '), DateTime.Parse(split[0].Remove(0, 5)));
                        Application.Current.Dispatcher.Invoke(() => LogEntries.Insert(0, logEntry));
                        if (Save == true)
                        {
                            WriteLogEntries.Add(logEntry);
                        }
                    }
                }
            }
            catch (ObjectDisposedException exception)
            {
                Console.WriteLine(exception.ToString());
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.ToString());
                MainWindow.main.Status = "Error";
            }
        }

        /// <summary>
        /// Write the Data in the File async.
        /// </summary>
        private async void WriteData()
        {
            while (true)
            {
                if (!string.IsNullOrEmpty(Path))
                {
                    using (StreamWriter sw = File.AppendText(Path))
                    {
                        LogEntry logEntry = WriteLogEntries.FirstOrDefault();
                        if (logEntry != null)
                        {
                            await sw.WriteLineAsync(logEntry.ToString());
                            WriteLogEntries.Remove(logEntry);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Clear the LogEntries.
        /// </summary>
        public void Clear()
        {
            LogEntries.Clear();
            LogText.Clear();
        }

        /// <summary>
        /// Stop ReadUdpData.
        /// </summary>
        public void Close()
        {
            UdpClient.Close();
        }

        /// <summary>
        /// Starts the ReadUdpData.
        /// </summary>
        public void Start()
        {
            IpEndPoint = new IPEndPoint(IPAddress.Any, Port);
            UdpClient = new UdpClient(IpEndPoint);
            UdpClient.BeginReceive(new AsyncCallback(ReadUdpData), "");
        }
    }
}
