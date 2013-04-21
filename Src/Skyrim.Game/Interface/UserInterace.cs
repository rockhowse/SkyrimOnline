using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.Game.Interface
{
    public class UserInterace
    {
        public UserInterace()
        {
            Skyrim.Script.Overlay.System.CursorVisible = false;
        }

        public void Update()
        {

        }

        public ChatInterface Chat
        {
            get;
            set;
        }
    }
}
