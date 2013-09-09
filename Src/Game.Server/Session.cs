#region

using System;
using System.Reflection;
using Game.API.Entities;
using Game.API.Networking;
using Game.API.Networking.Messages;
using Game.Server.Services;
using Lidgren.Network;
using log4net;

#endregion

namespace Game.Server
{
    public class Session
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private readonly NetConnection connection;
        private readonly PacketHandler handler = new PacketHandler();
        private readonly Player player;
        private readonly GameServer server;
        private readonly string username;

        public Session(NetConnection connection, GameServer server, string username)
        {
            this.connection = connection;
            this.server = server;
            this.username = username;

            handler.OnUpdatePlayerState += HandleUpdatePlayerStateMessage;
            handler.OnChatTalk += HandleChatTalkMessage;

            player = server.World.AddPlayer();

            SendMessageOrdered(new ChatTalkMessage("Welcome to the servers, press right ctrl to chat !"));
            SendMessageOrdered(new ChatTalkMessage("Type /help to see a list of available commands."));
        }

        public NetConnection Connection
        {
            get { return connection; }
        }

        public void HandlePacket(NetIncomingMessage inc)
        {
            handler.Handle(inc);
        }

        public void HandleUpdatePlayerStateMessage(IGameMessage msg)
        {
            UpdatePlayerStateMessage message = (UpdatePlayerStateMessage) msg;

            var timeDelay = (float) (NetTime.Now - connection.GetLocalTime(message.MessageTime));

            player.EnableSmoothing = true;

            if (player.LastUpdateTime < message.MessageTime)
            {
                player.SimulationState.Position = message.Position += message.Velocity*timeDelay;
                player.SimulationState.Velocity = message.Velocity;
                player.SimulationState.Rotation = message.Rotation;

                player.LastUpdateTime = message.MessageTime;
            }
        }

        public void HandleChatTalkMessage(IGameMessage msg)
        {
            ChatTalkMessage message = (ChatTalkMessage) msg;

            if (message.Message.Length > 1 && message.Message[0] == '/')
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
                om.Write((byte) gameMessage.MessageType);
                gameMessage.Encode(om);

                Connection.SendMessage(om, NetDeliveryMethod.ReliableUnordered, 0);
            }
            catch (Exception ex)
            {
                Logger.Error(ex.ToString());
            }
        }

        public void SendMessageOrdered(IGameMessage gameMessage)
        {
            try
            {
                NetOutgoingMessage om = server.CreateMessage();
                om.Write((byte) gameMessage.MessageType);
                gameMessage.Encode(om);

                Connection.SendMessage(om, NetDeliveryMethod.ReliableOrdered, 0);
            }
            catch (Exception ex)
            {
                Logger.Error(ex.ToString());
            }
        }
    }
}