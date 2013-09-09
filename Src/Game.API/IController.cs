namespace Game.API
{
    public abstract class IController
    {
        #region Input

        public abstract void EnableInput();
        public abstract void DisableInput();
        public abstract bool IsMenuMode();

        #endregion

        #region Game

        public abstract IActor PlaceAtMe();
        public abstract IActor GetPlayer();
        public abstract void PlayAnimation(IActor actor, string animationName);

        #endregion
    }
}