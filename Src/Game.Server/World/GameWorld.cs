using Game.API;
using Game.API.Entities;
using Game.API.Managers;
using Lidgren.Network;
using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Server.World
{
    public class GameWorld
    {
        private GameServer server;
        private PlayerManager playerManager;

        public GameWorld(GameServer server)
        {
            this.server = server;
            this.playerManager = new PlayerManager(true);
        }

        public void Update(GameTime timer)
        {
            playerManager.Update(timer);
        }

        public bool EnterWorld(NetIncomingMessage inc, out NetOutgoingMessage message)
        {
            message = server.CreateMessage();
            //new UpdatePlayerStateMessage(this.playerManager.AddPlayer(false)).Encode(hailMessage);
            return true;
        }

        public Player AddPlayer()
        {
            return playerManager.AddPlayer(false);
        }
    }
}
