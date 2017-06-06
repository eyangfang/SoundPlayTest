using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SoundPlayTest
{
    class ControlsCommand : ICommand
    {
        private MainViewModel obj;
        public ControlsCommand(MainViewModel _obj)
        {
            obj = _obj;
        }

        public bool CanExecute(object p)
        {
            return true;
        }

        public event EventHandler CanExecuteChanged;

        public void Execute(object p)
        {

        }
    }
}
