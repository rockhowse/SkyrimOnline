using Game.API.Networking.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Game.Server.Services
{
    public static class ChatService
    {
        public static void HandleCommand(Session session, GameServer server, ChatTalkMessage message)
        {
            var t = typeof(ChatService);
            var s = message.Message.Substring(1);
            s = s.Split(' ')[0];
            var m = t.GetMethod(s, BindingFlags.IgnoreCase | BindingFlags.Static | BindingFlags.Public | BindingFlags.Instance);
            if (m != null)
            {
                m.Invoke(null, new object[] { session, server, message });
            }
            else
                session.SendMessage(new ChatTalkMessage("This command is not valid !"));
        }

        public static void Users(Session session, GameServer server, ChatTalkMessage message)
        {
            session.SendMessage(new ChatTalkMessage("Currently " + server.SessionCount + " players are online."));
        }

        public static void Help(Session session, GameServer server, ChatTalkMessage message)
        {
            session.SendMessageOrdered(new ChatTalkMessage("/users : Display the number of players currently logged in."));
            session.SendMessageOrdered(new ChatTalkMessage("/help : Display this message."));
        }
    }
}
