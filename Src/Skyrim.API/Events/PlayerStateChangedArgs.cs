using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Skyrim.API.Entities;

namespace Skyrim.API.Events
{
    public class PlayerStateChangedArgs : EventArgs
    {
        public PlayerStateChangedArgs(Player player)
        {
            this.Player = player;
        }

        public Player Player { get; private set; }
    }
}
