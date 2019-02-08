/*using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LearingModeExample
{
    class ReceiveIr
    {
        const int START_LEARNING_MODE = 24;
        const int WAITING_IR_SIGNAL = 25;

        const int OK = 224; // Success response code from IR controller

        static int sCommandCode = 0;

        static SerialPort sSerialPort;

        static void Main(string[] args)
        {
            sSerialPort = new SerialPort("COM5");

            sSerialPort.BaudRate = 9600;
            sSerialPort.Parity = Parity.None;
            sSerialPort.StopBits = StopBits.One;
            sSerialPort.DataBits = 8;
            sSerialPort.Encoding = Encoding.ASCII;

            sSerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            sSerialPort.Open();

            // 224 - (E0) for learning single key
            // 225 - (E1) for learning key combination (some remotes send two ir codes for a single key)

            Console.WriteLine("Start learning mode ...");
            sCommandCode = START_LEARNING_MODE;
            sSerialPort.Write(new byte[] { 224 }, 0, 1);
            Console.ReadKey();

        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
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
                    Console.WriteLine("Ready to record the remote. Press any button now..");
                    sCommandCode = WAITING_IR_SIGNAL;
                }
                else
                {
                    Console.WriteLine("Error");
                }
            }
            else if (sCommandCode == WAITING_IR_SIGNAL)
            {
                Thread.Sleep(1500); // wait till buffer full

                int len = sSerialPort.BytesToRead;

                if (len > 0)
                {
                    Console.WriteLine("Got for IR signal....");

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
                        Console.WriteLine("Your ir signal:");
                        Console.WriteLine(ir_signal);
                    }
                    else
                    {
                        Console.WriteLine("Invalid checksum:");
                    }
                }
            }
        }
    }
}*/


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SendingModeExample
{
    class SendIr
    {
        const int START_LEARNING_MODE = 26;
        const int ERROR = 255;

        static SerialPort sSerialPort;

        // Past the ir code from learn example here.

        //Klasse: E58-2 Beamer EIN
        //const string ircode = "90,35,57,142,237,227,109,51,82,37,95,137,249,131,79,7,72,45,95,116,139,233,109,34,74,45,95,119,230,130,79,4,64,35,18,137,174,124,6,11,253,43,26,145,182,132,14,19,5,51,34,153,190,140,22,27,13,59,42,161,198,148,30,35,21,67,50,169,206,121,18,39,7,53,34,168,205,153,18,38,7,53,51,153,205,155,70,74,60,78";
        const string ircode = "180,35,237,140,239,240,89,71,72,175,94,19,248,248,78,185,70,164,94,119,26,18,78,4,64,35,18,137,174,124,6,11,253,43,26,145,182,132,14,19,5,51,34,153,190,140,22,27,13,59,42,161,198,148,30,35,21,67,50,169,206,156,38,43,29,75,58,177,214,121,34,22,7,52,34,152,204,137,18,22,24,68,35,152,188,137,18,22,7,52,34,152,188,137,18,22,7,52,51,152,188,139,2,38,7,52,34,152,188,153,18,22,7,69,50,153,188,137,18,22,7,52,34,152,204,138,18,22,8,68,34,152,188,137,35,39,24,68,35,153,204,137,18,22,7,52,34,169,204,137,18,22,7,69,50,152,188,137,18,22,7,52,35,152,204,137,34,22,7,52,34,152,188,137,19,22,7,53,53,115";

        //Klasse: E58-2 Beamer AUS
        //const string ircode = "89,35,55,142,239,228,109,53,82,36,95,136,249,130,79,8,72,45,95,103,139,234,109,35,74,45,95,119,230,130,79,4,64,35,18,137,174,124,6,11,253,43,26,145,182,132,14,19,5,51,34,153,190,140,22,27,13,59,42,161,198,148,30,35,21,67,50,169,206,121,18,39,7,53,34,168,205,153,19,23,7,53,50,168,205,155,70,75,8";

        static void Main(string[] args)
        {
            sSerialPort = new SerialPort("COM5");

            sSerialPort.BaudRate = 9600;
            sSerialPort.Parity = Parity.None;
            sSerialPort.StopBits = StopBits.One;
            sSerialPort.DataBits = 8;
            sSerialPort.Encoding = Encoding.ASCII;

            sSerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            sSerialPort.Open();

            Console.WriteLine("Sending IR Code ...");

            byte[] ir_array = ConvertStringArrayToByteArray(ircode);

            byte[] new_ir_array = new byte[ir_array.Length + 1];

            new_ir_array[0] = 227; // sending ir command.

            // copy ir code to this array starting from index 1
            for (int i = 1; i < ir_array.Length + 1; i++)
            {
                new_ir_array[i] = ir_array[i - 1];
            }

            sSerialPort.Write(new_ir_array, 0, new_ir_array.Length);
            Console.ReadKey();
        }

        private static byte[] ConvertStringArrayToByteArray(string str)
        {
            return str.Split(",".ToCharArray()).Select(x => byte.Parse(x.ToString())).ToArray();
        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            byte[] array = new byte[sSerialPort.BytesToRead];
            sSerialPort.Read(array, 0, sSerialPort.BytesToRead);

            int resvalue = array[0];

            if (resvalue == ERROR)
            {
                Console.WriteLine("Error sending ir !");
            }
            else
            {
                Console.WriteLine("Success!");
            }
        }
    }
}

