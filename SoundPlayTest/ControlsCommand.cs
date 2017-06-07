using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace SoundPlayTest
{
    public partial class ControlsCommand : ICommand
    {
        public event EventHandler CanExecuteChanged;
        private Action _action;
        private bool _canExecute;

        public ControlsCommand(Action action, bool canExecute)
        {
            _action = action;
            _canExecute = canExecute;
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute;
        }

        public void Execute(object parameter)
        {
            _action();
        }
        public void RaiseCanExecuteChanged(bool NewCanExecute)
        {
            _canExecute = NewCanExecute;
            if (CanExecuteChanged != null)
                CanExecuteChanged(this, new EventArgs());
        }
    }
}
