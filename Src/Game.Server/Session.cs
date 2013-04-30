using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game.API.Networking;
using Lidgren.Network;
using Game.API.Entities;
using Game.API.Networking.Messages;

namespace Game.Server
{
    public class Session
    {
        private PacketHandler handler = new PacketHandler();
        private NetConnection connection;
        private Player player;
        private GameServer server;

        public Session(NetConnection connection, GameServer server)
        {
            this.connection = connection;
            this.server = server;

            handler.OnUpdatePlayerState += HandleUpdatePlayerStateMessage;
            handler.OnChatTalk += HandleChatTalkMessage;

            player = server.World.AddPlayer();
        }

        public void HandlePacket(NetIncomingMessage inc)
        {
            handler.Handle(inc);
        }

        public void HandleUpdatePlayerStateMessage(IGameMessage msg)
        {
            UpdatePlayerStateMessage message = (UpdatePlayerStateMessage)msg;

            var timeDelay = (float)(NetTime.Now - connection.GetLocalTime(message.MessageTime));

            player.EnableSmoothing = true;

            if (player.LastUpdateTime < message.MessageTime)
            {
                player.SimulationState.Position = message.Position += message.Velocity * timeDelay;
                player.SimulationState.Velocity = message.Velocity;
                player.SimulationState.Rotation = message.Rotation;

                player.LastUpdateTime = message.MessageTime;
            }
        }

        public void HandleChatTalkMessage(IGameMessage msg)
        {
            ChatTalkMessage message = (ChatTalkMessage)msg;

            server.SendMessage(message);
        }

        public NetConnection Connection
        {
            get
            {
                return connection;
            }
        }
    }
}
