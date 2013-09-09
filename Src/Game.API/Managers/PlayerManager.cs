#region

using System;
using System.Collections.Generic;
using System.Threading;
using Game.API.Entities;
using Game.API.Events;
using Microsoft.Xna.Framework;

#endregion

namespace Game.API.Managers
{
    public class PlayerManager
    {
        private static long playerIdCounter;
        private readonly GameTimer hearbeatTimer;
        private readonly bool isHost;
        private readonly Dictionary<long, Player> players = new Dictionary<long, Player>();
        private Player localPlayer;

        public PlayerManager(bool isHost)
        {
            this.isHost = isHost;
            hearbeatTimer = new GameTimer();
        }

        public IEnumerable<Player> Players
        {
            get { return players.Values; }
        }

        public event EventHandler<PlayerStateChangedArgs> PlayerStateChanged;

        public Player AddPlayer(long id, Vector3 position, Vector3 velocity, float rotation, bool isLocal)
        {
            if (players.ContainsKey(id))
            {
                return players[id];
            }

            var player = new Player(
                id,
                new EntityState {Position = position, Rotation = rotation, Velocity = velocity});

            players.Add(player.Id, player);

            if (isLocal)
            {
                localPlayer = player;
            }

            return player;
        }

        public Player AddPlayer(bool isLocal)
        {
            EntityState physicsState = DefaultEntityState();

            Player player = AddPlayer(
                Interlocked.Increment(ref playerIdCounter),
                physicsState.Position,
                physicsState.Velocity,
                physicsState.Rotation,
                isLocal);

            return player;
        }

        public Player GetPlayer(long id)
        {
            if (players.ContainsKey(id))
            {
                return players[id];
            }

            return null;
        }

        public bool PlayerIsLocal(Player player)
        {
            return localPlayer != null && localPlayer.Id == player.Id;
        }

        public void RemovePlayer(long id)
        {
            if (players.ContainsKey(id))
            {
                players.Remove(id);
            }
        }

        public EntityState DefaultEntityState()
        {
            var physicsState = new EntityState
            {
                Position = new Vector3(0.0f)
            };

            return physicsState;
        }

        public void Update(GameTime gameTime)
        {
            if ((localPlayer != null) && (!localPlayer.IsDestroyed))
            {
                bool velocityChanged = HandlePlayerMovement();

                if (velocityChanged)
                {
                    OnPlayerStateChanged(localPlayer);
                }
            }

            foreach (Player player in Players)
            {
                player.Update(gameTime);

                if (!player.IsDestroyed)
                {
                }
            }

            if (isHost && hearbeatTimer.Stopwatch(200))
            {
                foreach (Player player in Players)
                {
                    OnPlayerStateChanged(player);
                }
            }
        }

        protected void OnPlayerStateChanged(Player player)
        {
            EventHandler<PlayerStateChangedArgs> playerStateChanged = PlayerStateChanged;
            if (playerStateChanged != null)
            {
                playerStateChanged(this, new PlayerStateChangedArgs(player));
            }
        }

        private bool HandlePlayerMovement()
        {
            bool velocityChanged = false;

            //Code to check for player movement

            return velocityChanged;
        }
    }
}