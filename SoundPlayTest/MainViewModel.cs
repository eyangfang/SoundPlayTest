using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using WindowsRuntimeComponent;
using System.Windows.Input;

namespace SoundPlayTest
{
    class MainViewModel : INotifyPropertyChanged
    {
        private AudioWrapper aw = new AudioWrapper();

        public event PropertyChangedEventHandler PropertyChanged;
        internal void RaisePropertyChanged(string prop)
        {
            if (PropertyChanged != null) { PropertyChanged(this, new PropertyChangedEventArgs(prop)); }
        }

        public ControlsCommand BtnCCmd { get; set; }
        public ControlsCommand BtnECmd { get; set; }
        private int sliderValueC;
        private int sliderValueE;
        public bool BtnCEnable { get; set; }
        public string BtnCText { get; set; }
        public bool BtnEEnable { get; set; }
        public string BtnEText { get; set; }
        public int SliderValueC
        {
            get { return sliderValueC; }
            set
            {
                sliderValueC = value;
                RaisePropertyChanged("SliderValue");
                cslider_ValueChanged();
            }
        }

        public int SliderValueE
        {
            get { return sliderValueE; }
            set
            {
                sliderValueE = value;
                RaisePropertyChanged("SliderValue");
                eslider_ValueChanged();
            }
        }

        private bool TaskCInProgress;
        private bool TaskEInProgress;

        public MainViewModel()
        {
            sliderValueC = 100;
            sliderValueE = 100;
            BtnCEnable = true;
            BtnCText = "Clockwise";
            BtnEEnable = true;
            BtnEText = "Elevation";
            BtnCCmd = new ControlsCommand(btnclock_Click, BtnCEnable);
            BtnECmd = new ControlsCommand(btnele_Click, BtnEEnable);
            TaskCInProgress = false;
            TaskEInProgress = false;
        }
        public void btnclock_Click()
        {
            if (!TaskCInProgress)
            {
                aw.Initialize();
                BtnCText = "Stop";
                RaisePropertyChanged("BtnCText");
                aw.SetMode(true);
            }
            else
            {
                aw.Stop();
                BtnCText = "Clockwise";
                RaisePropertyChanged("BtnCText");
            }
            BtnEEnable = !BtnEEnable;
            TaskCInProgress = !TaskCInProgress;
            BtnECmd.RaiseCanExecuteChanged(BtnEEnable);
            RaisePropertyChanged("BtnEEnable");
        }

        public void btnele_Click()
        {
            if (!TaskEInProgress)
            {
                aw.Initialize();
                BtnEText = "Stop";
                RaisePropertyChanged("BtnEText");
                aw.SetMode(false);
            }
            else
            {
                aw.Stop();
                BtnEText = "Elevation";
                RaisePropertyChanged("BtnEText");
            }
            BtnCEnable = !BtnCEnable;
            TaskEInProgress = !TaskEInProgress;
            BtnCCmd.RaiseCanExecuteChanged(BtnCEnable);
            RaisePropertyChanged("BtnCEnable");
        }

        private void cslider_ValueChanged()
        {
            aw.SetDistance(sliderValueC, true);
        }

        private void eslider_ValueChanged()
        {
             aw.SetDistance(sliderValueE, false);
        }
    
    }
}
