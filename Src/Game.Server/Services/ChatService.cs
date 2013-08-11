using Game.API.Networking.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Server.Services
{
    public static class ChatService
    {
        public static void Users(Session session, GameServer server, ChatTalkMessage message)
        {
            session.SendMessage(new ChatTalkMessage("Currently " + server.SessionCount + " players are online."));
        }
    }
}
