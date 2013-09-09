#region

using Game.API;

#endregion

namespace Game.Client.Interface
{
    public class UserInterace
    {
        public UserInterace()
        {
            Overlay.System.CursorVisible = false;
        }

        public ChatInterface Chat { get; set; }

        public void Update()
        {
            if (GlobalContext.Controller.IsMenuMode())
            {
                Overlay.System.CursorVisible = false;
                Chat.Visible = false;
            }
            else
            {
                Chat.Visible = true;
            }
        }
    }
}