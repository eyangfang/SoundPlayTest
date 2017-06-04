using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using WindowsRuntimeComponent;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace SoundPlayTest
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void btnclock_Click(object sender, RoutedEventArgs e)
        {
            if (btnclock.Content.ToString() == "Clockwise")
            {
                AudioWrapper aw = new AudioWrapper();
                aw.Initialize();
                btnclock.Content = "Stop";
                btnele.IsEnabled = false;
                eslider.IsEnabled = false;
            }
            else
            {
                btnclock.Content = "Clockwise";
                btnele.IsEnabled = true;
                eslider.IsEnabled = true;
            }
        }

        private void btnele_Click(object sender, RoutedEventArgs e)
        {
            if (btnele.Content.ToString() == "Elevation")
            {
                btnele.Content = "Stop";
                btnclock.IsEnabled = false;
                cslider.IsEnabled = false;
            }
            else
            {
                btnele.Content = "Elevation";
                btnclock.IsEnabled = true;
                cslider.IsEnabled = true;
            }
        }
    }
}
