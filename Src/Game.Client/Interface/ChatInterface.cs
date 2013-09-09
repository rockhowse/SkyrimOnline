#region

using Game.API.Networking.Messages;
using Game.Overlay;
using G = Game;

#endregion

namespace Game.Client.Interface
{
    public class ChatInterface
    {
        private readonly Chat m_chat;

        public ChatInterface()
        {
            m_chat = new Chat();
            m_chat.Visible = true;
            m_chat.OnInput += OnChatInput;

            Overlay.System.Register(m_chat);
        }

        public bool Visible
        {
            get { return m_chat.Visible; }
            set { m_chat.Visible = value; }
        }

        public void Log(string str)
        {
            m_chat.Log(str);
        }

        private void OnChatInput(string str)
        {
            ChatTalkMessage message = new ChatTalkMessage(str);

            Entry.GameClient.SendMessage(message);
        }
    }
}