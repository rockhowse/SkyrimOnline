using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using G = Game;

namespace Skyrim.Game.Interface
{
    public class UserInterace
    {
        public UserInterace()
        {
            G.Overlay.System.CursorVisible = false;
        }

        public ChatInterface Chat
        {
            get;
            set;
        }
    }
}
