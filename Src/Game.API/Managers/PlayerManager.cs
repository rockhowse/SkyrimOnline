using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Game.API.Entities;
using Game.API.Events;
using Microsoft.Xna.Framework;

namespace Game.API.Managers
{
    public class PlayerManager
    {
        private readonly bool isHost;
        private readonly Dictionary<long, Player> players = new Dictionary<long, Player>();
        private static long playerIdCounter;
        private GameTimer hearbeatTimer;
        private Player localPlayer;

        public event EventHandler<PlayerStateChangedArgs> PlayerStateChanged;

        public PlayerManager(bool isHost)
        {
            this.isHost = isHost;
            this.hearbeatTimer = new GameTimer();
        }

        public IEnumerable<Player> Players
        {
            get
            {
                return this.players.Values;
            }
        }

        public Player AddPlayer(long id, Vector3 position, Vector3 velocity, float rotation, bool isLocal)
        {
            if (this.players.ContainsKey(id))
            {
                return this.players[id];
            }

            var player = new Player(
                id,
                new EntityState { Position = position, Rotation = rotation, Velocity = velocity });

            this.players.Add(player.Id, player);

            if (isLocal)
            {
                this.localPlayer = player;
            }

            return player;
        }

        public Player AddPlayer(bool isLocal)
        {
            EntityState physicsState = this.DefaultEntityState();

            Player player = this.AddPlayer(
                Interlocked.Increment(ref playerIdCounter),
                physicsState.Position,
                physicsState.Velocity,
                physicsState.Rotation,
                isLocal);

            return player;
        }

        public Player GetPlayer(long id)
        {
            if (this.players.ContainsKey(id))
            {
                return this.players[id];
            }

            return null;
        }

        public bool PlayerIsLocal(Player player)
        {
            return this.localPlayer != null && this.localPlayer.Id == player.Id;
        }

        public void RemovePlayer(long id)
        {
            if (this.players.ContainsKey(id))
            {
                this.players.Remove(id);
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
            if ((this.localPlayer != null) && (!this.localPlayer.IsDestroyed))
            {
                bool velocityChanged = this.HandlePlayerMovement();

                if (velocityChanged)
                {
                    this.OnPlayerStateChanged(this.localPlayer);
                }
            }

            foreach (Player player in this.Players)
            {
                player.Update(gameTime);

                if (!player.IsDestroyed)
                {

                }
            }

            if (this.isHost && this.hearbeatTimer.Stopwatch(200))
            {
                foreach (Player player in this.Players)
                {
                    this.OnPlayerStateChanged(player);
                }
            }
        }

        protected void OnPlayerStateChanged(Player player)
        {
            EventHandler<PlayerStateChangedArgs> playerStateChanged = this.PlayerStateChanged;
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
