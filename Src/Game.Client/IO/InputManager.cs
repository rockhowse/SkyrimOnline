using Game;
using Game.API;
using Game.API.Utilities;
using Game.Script;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Client.IO
{
    public class InputManager
    {
        private bool mUIEnabled;

        public InputManager()
        {
            UIEnabled = false;
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
                            KeyboardEvent ev = (KeyboardEvent)e;
                            OnEvent(ev);
                            break;
                        }

                    case EventType.kMouse:
                        {
                            MouseEvent ev = (MouseEvent)e;
                            OnEvent(ev);
                            break;
                        }

                    case EventType.kPosition:
                        {
                            MousePositionEvent ev = (MousePositionEvent)e;
                            OnEvent(ev);
                            break;
                        }
                }
            }
        }

        public void OnEvent(KeyboardEvent ev)
        {
            // F3 - http://community.bistudio.com/wiki/DIK_KeyCodes
            if (ev.Key == 0x9D && ev.Pressed == true)
            {
                UIEnabled = !UIEnabled;
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

        public bool UIEnabled
        {
            get
            {
                return mUIEnabled;
            }
            set
            {
                if(value)
                    GlobalFactory.Controller.DisableInput();
                else
                    GlobalFactory.Controller.EnableInput();

                Overlay.System.CursorVisible = value;
                mUIEnabled = value;
            }
        }
    }
}
