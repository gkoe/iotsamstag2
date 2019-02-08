using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using UdpLogger.Entities;

namespace UdpLogger
{

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private LogUdpClient _logUdpClient;

        internal static MainWindow main;

        internal string Status
        {
            set { Dispatcher.Invoke(new Action(() => { label_status.Content = value; })); }
        }

        public MainWindow()
        {
            main = this;
            _logUdpClient = new LogUdpClient();
            InitializeComponent();
            dg_messages.ItemsSource = _logUdpClient.LogEntries;
            lb_textBlank.ItemsSource = _logUdpClient.LogText;
            tb_port.Text = "49155";
            label_status.Content = "Starting";
            tb_search.Text = Environment.ExpandEnvironmentVariables(@"%USERPROFILE%\Desktop") + "UdpData" + DateTime.Now.ToShortDateString() + ".csv";
            _logUdpClient.Path = tb_search.Text;
        }

        /// <summary>
        /// This Method starts or stop the UdpLogger.
        /// Also Search for wrong input. (Port) 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Bt_start_Click(object sender, RoutedEventArgs e)
        {
            if ((string)bt_start.Content == "Stop")
            {
                bt_start.Content = "Start";
                _logUdpClient.Close();
                label_status.Content = "Stopped";
            }
            else
            {
                if (tb_port.Text == "")
                {
                    lb_validate.Content = new TextBlock() { Text = "You must write a Number into the Textbox.", TextWrapping = TextWrapping.Wrap }; 
                }
                else
                {
                    _logUdpClient.Port = -1;
                    try
                    {
                        _logUdpClient.Port = Convert.ToInt32(tb_port.Text);
                    }
                    catch (Exception)
                    {
                        lb_validate.Content = "You must write a Number";
                    }
                    if (_logUdpClient.Port > 0 && _logUdpClient.Port <= 65535)
                    {
                        lb_validate.Content = "";
                        bt_start.Content = "Stop";
                        try
                        {
                            label_status.Content = "Working";
                            _logUdpClient.Start();
                        }
                        catch (Exception)
                        {
                            label_status.Content = "Error";
                        }
                    }
                    else if(_logUdpClient.Port == 0)
                    {
                        lb_validate.Content = "0 is not a valid Port";
                    }
                    else if(_logUdpClient.Port > 65535)
                    {
                        lb_validate.Content = _logUdpClient.Port + " is not a valid Port";
                    }
                }
            }
        }

        /// <summary>
        /// Clears the UdpLogger 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Bt_clear_Click(object sender, RoutedEventArgs e)
        {
            _logUdpClient.Clear();
        }

        /// <summary>
        /// FileDialog to choose the File where Data shoud be saved.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Bt_search_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "CSV Files (*.csv)|*.csv";
            dialog.InitialDirectory = Environment.ExpandEnvironmentVariables(@"%USERPROFILE%\Desktop");
            DialogResult result = dialog.ShowDialog();
            if (result.ToString() == "OK")
            {
                tb_search.Text = dialog.FileName;
                _logUdpClient.Path = tb_search.Text;
            }
        }

        /// <summary>
        /// Set the write variable to true or false.
        /// Also make a DataGrid Visible for choosing the File to save.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Cb_saveInFile_Click(object sender, RoutedEventArgs e)
        {
            if(cb_saveInFile.IsChecked == true)
            {
                grid_File.Visibility = Visibility.Visible;
                _logUdpClient.Save = true;
            }
            else
            {
                _logUdpClient.Save = false;
                grid_File.Visibility = Visibility.Hidden;
            }
        }
    }
}
