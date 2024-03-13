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

namespace RobotInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        bool isRoyalBlue;
        
        public MainWindow()
        {
            InitializeComponent();
        }

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
            textBoxReception.Text += "Reçu : " + textBoxEmission.Text + "\n";
            textBoxEmission.Text = "";
        }

        private void TextBoxEmission_Keyup(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMessage();
                
            }

        }
    }
}
