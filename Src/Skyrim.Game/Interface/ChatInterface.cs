using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.Game.Interface
{
    public class ChatInterface
    {
        private Skyrim.Script.Overlay.Chat m_chat;

        public ChatInterface()
        {
            m_chat = new Skyrim.Script.Overlay.Chat();
            m_chat.Visible = true;

            Skyrim.Script.Overlay.System.Register(m_chat);
        }

        public void Log(string str)
        {
            m_chat.Log(str);
        }
    }
}
