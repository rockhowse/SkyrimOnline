using Game.API;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Game.Client
{
    class World : IWorld
    {
        private Int64 time = 0;

        public void Update()
        {
            long ticks = DateTime.UtcNow.Ticks;
            if ((ticks - time) / 10000000 > 5)
            {
                time = ticks;
                Entry.UserInterace.Chat.Log(GlobalFactory.Module.Name);
            }
        }
    }
}
