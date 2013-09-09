#region

using System;
using Game.API.Entities;

#endregion

namespace Game.API.Events
{
    public class PlayerStateChangedArgs : EventArgs
    {
        public PlayerStateChangedArgs(Player player)
        {
            Player = player;
        }

        public Player Player { get; private set; }
    }
}