using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using G = Game;

namespace Game.Client.Interface
{
    public class ChatInterface
    {
        private G.Overlay.Chat m_chat;

        public ChatInterface()
        {
            m_chat = new G.Overlay.Chat();
            m_chat.Visible = true;

            G.Overlay.System.Register(m_chat);
        }

        public void Log(string str)
        {
            m_chat.Log(str);
        }
    }
}
