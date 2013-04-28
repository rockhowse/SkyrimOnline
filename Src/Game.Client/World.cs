using Game.API;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Game.API.Utilities;

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
                if (GlobalFactory.Module.GameType == GameType.kOblivion)
                {
                    var actor = Game.Script.Oblivion.Game.GetPlayer();
                    Entry.UserInterace.Chat.Log(actor.Position.X.ToString());
                }
                time = ticks;
                Entry.UserInterace.Chat.Log(GlobalFactory.Module.Name);
            }
        }
    }
}
