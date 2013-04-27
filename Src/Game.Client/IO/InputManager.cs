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
            Entry.UserInterace.Chat.Log(ev.Key + " " + ev.Pressed);
            // F3 - http://community.bistudio.com/wiki/DIK_KeyCodes
            if (ev.Key == 0x3D && ev.Pressed == true)
            {
                UIEnabled = !UIEnabled;
                if (UIEnabled)
                {
                    switch (GlobalFactory.Module.GameType)
                    {
                        case GameType.kSkyrim:
                            Game.Script.Skyrim.Game.DisablePlayerControls(true, true, true, true, true, true, true, true, 1);
                            break;
                    }
                    
                }
                else
                {
                    switch (GlobalFactory.Module.GameType)
                    {
                        case GameType.kSkyrim:
                            Game.Script.Skyrim.Game.EnablePlayerControls(true, true, true, true, true, true, true, true, 1);
                            Game.Script.Skyrim.Game.SetInChargen(false, false, true);
                            break;
                    }
                }
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
                Overlay.System.CursorVisible = value;
                mUIEnabled = value;
            }
        }
    }
}
