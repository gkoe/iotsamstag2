using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace IRDevkitWPF
{


    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const int START_LEARNING_MODE = 24;
        const int WAITING_IR_SIGNAL = 25;

        const int OK = 224; // Success response code from IR controller
        
        static int sCommandCode = 0;

        static SerialPort sSerialPort;

        public MainWindow()
        {
        

        }



        private void Learning_mode_Click(object sender, RoutedEventArgs e)
        {
            sSerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            sSerialPort.Open();

            // 224 - (E0) for learning single key
            // 225 - (E1) for learning key combination (some remotes send two ir codes for a single key)
            Btn_Learning_mode.Content = "Stop";
            TBLShowlines.Inlines.Add("Start learning mode ...\n");
            sCommandCode = START_LEARNING_MODE;
            sSerialPort.Write(new byte[] { 224 }, 0, 1);
          

            
        }



        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {

            //0xff - Command error / Learning error / The infrared code is empty or invalid
            //0x00 - success


            if (sCommandCode == START_LEARNING_MODE)
            {
                // Response from start learning mode

                byte[] array = new byte[sSerialPort.BytesToRead];
                sSerialPort.Read(array, 0, sSerialPort.BytesToRead);

                int resvalue = array[0];

                if (resvalue == OK)
                {
                   // TBLShowlines.Inlines.Add("Ready to record the remote. Press any button now..");
                    sCommandCode = WAITING_IR_SIGNAL;
                }
                else
                {
                    //TBLShowlines.Inlines.Add("Error");
                }
            }
            else if (sCommandCode == WAITING_IR_SIGNAL)
            {
                Thread.Sleep(1500); // wait till buffer full

                int len = sSerialPort.BytesToRead;

                if (len > 0)
                {
                    //TBLShowlines.Inlines.Add("Got for IR signal....");

                    byte[] buffer = new byte[sSerialPort.BytesToRead];
                    sSerialPort.Read(buffer, 0, sSerialPort.BytesToRead);
                    string ir_signal = "";
                    int num = 0;

                    for (int idx = 0; idx < len; idx++)
                    {
                        ir_signal += buffer[idx];

                        // If not the last index, append "," to string
                        if (idx + 1 != len)
                        {
                            ir_signal += ",";
                        }

                        // Ignore the last digit in the array. It is the checksum
                        if (idx != len - 1)
                        {
                            num += buffer[idx];
                        }
                    }

                    // received data checksum
                    byte received_checksum = (byte)num;

                    // ir signal checksum is the last byte
                    int ir_signal_checksum = buffer[len - 1];

                    if (received_checksum == ir_signal_checksum)
                    {

                        this.Dispatcher.Invoke(DispatcherPriority.Normal, new Action(() =>
                        {
                            TBir.Text = ir_signal;
                        }));
                       
                       
                    }
                    else
                    {
                       // Console.WriteLine("Invalid checksum:");
                    }
                }
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            string filePath = @"C:\temp\ircodes.csv";
            sSerialPort = new SerialPort("COM6");

            sSerialPort.BaudRate = 9600;
            sSerialPort.Parity = Parity.None;
            sSerialPort.StopBits = StopBits.One;
            sSerialPort.DataBits = 8;
            sSerialPort.Encoding = Encoding.ASCII;
            TBLbtnavail.Inlines.Add("Vorhandene Button: \n \n");
            /*Dictionary<string, string> allir = ReadFromCsv(filePath);
            foreach (KeyValuePair<string, string> pair in allir)
            {
                TBLbtnavail.Inlines.Add(pair.Key + "\n");
            }*/
         
        }

        private void BTNSave_Click(object sender, RoutedEventArgs e)
        {
            string filePath = @"C:\temp\ircodes.csv";
            string delimiter = ";";
            Dictionary<string, string> allir = ReadFromCsv(filePath);

            for (int i = 0; i < allir.Count; i++)
            {
               
            }

            int length = allir.Count;
            StringBuilder sb = new StringBuilder();
            foreach(KeyValuePair<string, string> pair in allir)
            {
                if(pair.Key == TBirname.Text && pair.Value == TBir.Text)
                {
                    sb.AppendLine(pair.Key + delimiter + TBir.Text);
                }
                else
                {
                    if(pair.Key == TBirname.Text)
                    {
                        sb.AppendLine(pair.Key + delimiter + TBir.Text);

                    }
                    else
                    {

                    sb.AppendLine(pair.Key + delimiter + pair.Value);
                    }

                }
               
            }

            sb.AppendLine(TBirname.Text + delimiter + TBir.Text);
      
            File.WriteAllText(filePath, sb.ToString());
            TBLShowlines.Inlines.Add(TBirname.Text +" saved!!\n");
            Btn_Learning_mode.Content = "Start";
            TBir.Text = "";
            TBirname.Text = "";

            sSerialPort.Close();
        }

        private Dictionary<string,string> ReadFromCsv(string path)
        {
            string[] help;
            Dictionary<string, string> allir = new Dictionary<string, string>();
            string[] readText = File.ReadAllLines(path);
            foreach(string s in readText)
            {
                help = s.Split(';');

                allir.Add(help[0], help[1]);
            }

            return allir;
        }
    }
}
