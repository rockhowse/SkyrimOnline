using Game.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkyrimS = Game.Script.Skyrim;

namespace Game.Client.Controllers
{
    public class SkyrimController : Game.API.IController
    {
        #region Input

        public override void EnableInput() 
        {
            SkyrimS.Game.EnablePlayerControls(true, true, true, true, true, true, true, true, 1);
            SkyrimS.Game.SetInChargen(false, false, true);
        }

        public override void DisableInput()
        {
            SkyrimS.Game.DisablePlayerControls(true, true, true, true, true, true, true, true, 1);
        }

        public override bool IsMenuMode()
        {
            return false;
        }

        #endregion

#region Game

        public override IActor PlaceAtMe()
        {
            return SkyrimS.Game.PlaceAtMe(SkyrimS.Game.GetPlayer(), 7);
        }

        public override IActor GetPlayer()
        {
            return SkyrimS.Game.GetPlayer();
        }

        public override void PlayAnimation(IActor actor, string animationName)
        {
            SkyrimS.Debug.SendAnimationEvent(actor, animationName);
        }
#endregion
    }
}
