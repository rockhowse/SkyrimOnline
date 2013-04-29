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
            m_chat.OnInput += OnChatInput;

            G.Overlay.System.Register(m_chat);
        }

        public void Log(string str)
        {
            m_chat.Log(str);
        }

        public bool Visible
        {
            get { return m_chat.Visible; }
            set { m_chat.Visible = value; }
        }

        private void OnChatInput(string str)
        {
            Log("Chat input : " + str);
        }
    }
}
