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
        private IActor actor = null;

        public void Update()
        {
            long ticks = DateTime.UtcNow.Ticks;
            if ((ticks - time) / 10000000 > 5)
            {
                //if (actor == null)
                {
                    actor = GlobalContext.Controller.PlaceAtMe();
                    //actor.EnableAI(false);
                }
                //GlobalContext.Controller.PlayAnimation(actor, "JumpStandingStart");

                Entry.UserInterace.Chat.Log("PlaceAtMe");
                time = ticks;
            }
        }

        public void OnEnter()
        {
            time = DateTime.UtcNow.Ticks;
        }
    }
}
