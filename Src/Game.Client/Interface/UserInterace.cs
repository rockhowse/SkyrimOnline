using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game;

namespace Game.Client.Interface
{
    public class UserInterace
    {
        public UserInterace()
        {
            Overlay.System.CursorVisible = false;
        }

        public ChatInterface Chat
        {
            get;
            set;
        }
    }
}
