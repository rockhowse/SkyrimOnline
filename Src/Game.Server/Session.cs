using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game.API.Networking;
using Lidgren.Network;
using Game.API.Entities;
using Game.API.Networking.Messages;
using log4net;
using System.Reflection;
using Game.Server.Services;

namespace Game.Server
{
    public class Session
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private PacketHandler handler = new PacketHandler();
        private NetConnection connection;
        private Player player;
        private GameServer server;
        private string username;

        public Session(NetConnection connection, GameServer server, string username)
        {
            this.connection = connection;
            this.server = server;
            this.username = username;
            
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

            if(message.Message.Length > 1 && message.Message[0] == '/')
            {
                Logger.Info("[" + username + "] issued command " + message.Message);
                ChatService.HandleCommand(this, server, message);
                return;
            }

            Logger.Info("[" + username + "]: " + message.Message);
            
            server.SendMessage(new ChatTalkMessage("[" + username + "]: " + message.Message));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            try
            {
                NetOutgoingMessage om = server.CreateMessage();
                om.Write((byte)gameMessage.MessageType);
                gameMessage.Encode(om);

                Connection.SendMessage(om, NetDeliveryMethod.ReliableUnordered, 0);
            }
            catch (System.Exception ex)
            {
                Logger.Error(ex.ToString());
            }
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
