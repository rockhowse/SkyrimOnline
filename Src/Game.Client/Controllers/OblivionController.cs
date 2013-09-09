#region

using Game.API;
using OblivionS = Game.Script.Oblivion;

#endregion

namespace Game.Client.Controllers
{
    public class OblivionController : IController
    {
        #region Input        

        public override void EnableInput()
        {
            OblivionS.Game.EnableMouse();
            OblivionS.Game.EnablePlayerControls();
        }

        public override void DisableInput()
        {
            OblivionS.Game.DisablePlayerControls();
            OblivionS.Game.DisableMouse();
        }

        public override bool IsMenuMode()
        {
            return OblivionS.Game.IsMenuMode();
        }

        #endregion

        #region Game

        public override IActor PlaceAtMe()
        {
            return OblivionS.Game.PlaceAtMe(OblivionS.Game.GetPlayer(), 0x0003DB35);
        }

        public override IActor GetPlayer()
        {
            return OblivionS.Game.GetPlayer();
        }

        public override void PlayAnimation(IActor actor, string animationName)
        {
            // throw new NotImplementedException();
        }

        #endregion
    }
}