using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using ExtendedSerialPort_NS;
using System.IO.Ports;
using System.Windows.Threading;

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ExtendedSerialPort serialPort1;
        bool isRoyalBlue;
        
        public MainWindow()
        {
            InitializeComponent();
           serialPort1 = new ExtendedSerialPort("COM21", 115200, Parity.None, 8, StopBits.One); // Initialize the serial port
         //   serialPort1 = new ReliableSerialPort("COM21", 115200, Parity.None, 8, StopBits.One);

            serialPort1.DataReceived += SerialPort1_DataReceived; 

            serialPort1.Open();                                                                 // Open the serial port


            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();


        }

        string receivedText = "";

        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            if (receivedText != "")
            {
                textBoxReception.Text += receivedText;
                receivedText = "";
            }
        }
        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
           
            receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            //textBoxReception.Text += receivedText;
        }

        DispatcherTimer timerAffichage;




        private void ButtonEnvoyer_Click(object sender, RoutedEventArgs e)
        {

            if (isRoyalBlue) {

                ButtonEnvoyer.Background = Brushes.Beige;
                isRoyalBlue= false;
            }
            else {
                ButtonEnvoyer.Background = Brushes.RoyalBlue;
                isRoyalBlue = true;
            }
            SendMessage();
           
        }
        private void SendMessage()
        {
            serialPort1.WriteLine(textBoxEmission.Text);
            //textBoxReception.Text += "Reçu : " + textBoxEmission.Text + "\n";
            textBoxEmission.Text = "";


        }

        private void TextBoxEmission_Keyup(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMessage();
                
            }

        }

        private void ButtonClear_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ButtonTest_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
