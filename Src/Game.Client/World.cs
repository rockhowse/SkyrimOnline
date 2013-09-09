#region

using System;
using Game.API;

#endregion

namespace Game.Client
{
    internal class World : IWorld
    {
        private IActor actor = null;
        private Int64 time;

        public void Update()
        {
            long ticks = DateTime.UtcNow.Ticks;
            /*if ((ticks - time) / 10000000 > 5)
            {
                //if (actor == null)
                {
                    actor = GlobalContext.Controller.PlaceAtMe();
                    //actor.EnableAI(false);
                }
                //GlobalContext.Controller.PlayAnimation(actor, "JumpStandingStart");

                Entry.UserInterace.Chat.Log("PlaceAtMe");
                time = ticks;
            }*/
        }

        public void OnEnter()
        {
            time = DateTime.UtcNow.Ticks;
        }
    }
}