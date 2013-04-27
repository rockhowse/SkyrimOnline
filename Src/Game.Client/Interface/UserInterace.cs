using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game;
using Game.API.Utilities;
using Game.API;

namespace Game.Client.Interface
{
    public class UserInterace
    {
        public UserInterace()
        {
            Overlay.System.CursorVisible = false;
        }

        public void Update()
        {
            if (GlobalFactory.Module.GameType == GameType.kOblivion)
            {
                if (Game.Script.Oblivion.Game.IsMenuMode())
                {
                    Overlay.System.CursorVisible = false;
                    this.Chat.Visible = false;
                }
                else
                {
                    this.Chat.Visible = true;
                }
            }
        }

        public ChatInterface Chat
        {
            get;
            set;
        }
    }
}
