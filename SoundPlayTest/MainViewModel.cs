using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace SoundPlayTest
{
    class MainViewModel
    {
        private MainPage obj = new MainPage();

        private ControlsCommand objCommand;

        public MainViewModel()
        {
            objCommand = new ControlsCommand(this);
        }
    }
}
