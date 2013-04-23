using Game;
using Game.Script;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using G = Game;

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
            while ((e = G.Input.Poll()) != null)
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
            if (ev.Key == 0x3D && ev.Pressed == true)
            {
                UIEnabled = !UIEnabled;
            }
            if (UIEnabled)
            {
                G.Overlay.System.InjectKeyboardKey(ev.Key, ev.Pressed);
                Game.Script.Skyrim.Game.DisablePlayerControls(true, true, true, true, true, true, true, true, 1);
            }
            else
            {
                Game.Script.Skyrim.Game.EnablePlayerControls(true, true, true, true, true, true, true, true, 1);
                Game.Script.Skyrim.Game.SetInChargen(false, false, true);
            }
        }

        public void OnEvent(MouseEvent ev)
        {
            if (UIEnabled)
                G.Overlay.System.InjectMouseKey(ev.Key, ev.Pressed);
        }

        public void OnEvent(MousePositionEvent ev)
        {
            if (UIEnabled)
                G.Overlay.System.InjectMousePosition(ev.X, ev.Y, ev.Z);
        }

        public bool UIEnabled
        {
            get
            {
                return mUIEnabled;
            }
            set
            {
                G.Overlay.System.CursorVisible = value;
                mUIEnabled = value;
            }
        }
    }
}
