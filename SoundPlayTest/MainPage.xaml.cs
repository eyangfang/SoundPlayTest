using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.Resources.Core;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

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

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string language;
            ComboBox comboBox = sender as ComboBox;
            switch (comboBox.SelectedIndex)
            {
                case 0:
                    language = "en-US"; break;
                case 1:
                    language = "zh-CN"; break;
                default: return;
            }
            Windows.Globalization.ApplicationLanguages.PrimaryLanguageOverride = language;
            ResetControls(language);
            
        }

        private void ResetControls(string language)
        {
            ResourceContext resourceContext = new ResourceContext();
            resourceContext.Languages = new string[] { language };
            ResourceMap resourceMap = ResourceManager.Current.MainResourceMap.GetSubtree("Resources");
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            cmbLanguageSelect.SelectedIndex = 0;
            try
            {
                int selectedIndex = Convert.ToInt32(e.Parameter);
                if (selectedIndex < cmbLanguageSelect.Items.Count && selectedIndex > -1)
                {
                    cmbLanguageSelect.SelectedIndex = selectedIndex;
                }
            }
            catch { }
            cmbLanguageSelect.SelectionChanged += ComboBox_SelectionChanged;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage), cmbLanguageSelect.SelectedIndex);
        }
    }
}
