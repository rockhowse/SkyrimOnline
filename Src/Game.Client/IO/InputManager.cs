#region

using Game.API;

#endregion

namespace Game.Client.IO
{
    public class InputManager
    {
        private bool mUIEnabled;

        public InputManager()
        {
            UIEnabled = false;
        }

        public bool UIEnabled
        {
            get { return mUIEnabled; }
            set
            {
                Overlay.System.CursorVisible = value;
                mUIEnabled = value;
            }
        }

        public void Update()
        {
            Event e = null;
            while ((e = Input.Poll()) != null)
            {
                switch (e.Type)
                {
                    case EventType.kKeyboard:
                    {
                        KeyboardEvent ev = (KeyboardEvent) e;
                        OnEvent(ev);
                        break;
                    }

                    case EventType.kMouse:
                    {
                        MouseEvent ev = (MouseEvent) e;
                        OnEvent(ev);
                        break;
                    }

                    case EventType.kPosition:
                    {
                        MousePositionEvent ev = (MousePositionEvent) e;
                        OnEvent(ev);
                        break;
                    }
                }
            }
        }

        public void OnEvent(KeyboardEvent ev)
        {
            // F3 - http://community.bistudio.com/wiki/DIK_KeyCodes
            /* if (ev.Pressed)
            {
                Entry.UserInterace.Chat.Log("Pressed key : " + ev.Key.ToString());
            }
            else
            {
                Entry.UserInterace.Chat.Log("Released key : " + ev.Key.ToString());
            }*/
            if (ev.Key == 0x9D && ev.Pressed)
            {
                UIEnabled = !UIEnabled;
                if (UIEnabled)
                    GlobalContext.Controller.DisableInput();
                else
                    GlobalContext.Controller.EnableInput();
            }

            if (UIEnabled)
            {
                Overlay.System.InjectKeyboardKey(ev.Key, ev.Pressed);
            }
        }

        public void OnEvent(MouseEvent ev)
        {
            if (UIEnabled)
                Overlay.System.InjectMouseKey(ev.Key, ev.Pressed);
        }

        public void OnEvent(MousePositionEvent ev)
        {
            if (UIEnabled)
                Overlay.System.InjectMousePosition(ev.X, ev.Y, ev.Z);
        }
    }
}