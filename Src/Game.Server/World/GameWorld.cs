using Game.API;
using Game.API.Entities;
using Game.API.Managers;
using Game.API.Networking;
using Game.API.Networking.Messages;
using Lidgren.Network;
using log4net;
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Game.Server.World
{
    public class GameWorld
    {
        private GameServer server;
        private PlayerManager playerManager;

        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        public GameWorld(GameServer server)
        {
            this.server = server;
            this.playerManager = new PlayerManager(true);
        }

        public void Update(GameTime timer)
        {
            playerManager.Update(timer);
        }

        public bool EnterWorld(NetIncomingMessage inc, out NetOutgoingMessage message, out string username)
        {
            message = server.CreateMessage();
            username = null;

            if (inc.SenderConnection.RemoteHailMessage != null)
            {
                // Read opcode
                GameMessageTypes opcode = (GameMessageTypes)inc.SenderConnection.RemoteHailMessage.ReadByte();
                if (opcode != GameMessageTypes.HandShake)
                    return false;

                HandShakeMessage msg = new HandShakeMessage(inc.SenderConnection.RemoteHailMessage);
                if (msg.Version == Game.API.Networking.PacketHandler.PROTOCOL_VERSION && msg.Username != null && msg.Username.Length != 0)
                {
                    username = msg.Username;
                    return true;
                }
            }
            return false;
            
            //new UpdatePlayerStateMessage(this.playerManager.AddPlayer(false)).Encode(hailMessage);
            
        }

        public Player AddPlayer()
        {
            return playerManager.AddPlayer(false);
        }
    }
}
