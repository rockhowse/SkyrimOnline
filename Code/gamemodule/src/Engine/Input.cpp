#include <Engine\Input.h>

namespace GameModule
{
	namespace Engine
	{
		namespace Input
		{
			InputListener* TheInputListener = nullptr;

			void UnmanagedInputListener::OnPress(BYTE code)
			{
				unsigned char Key = code;

				if (MyGUI::InputManager::getInstance().isFocusKey() == false && Key == DIK_RCONTROL) // Right CTRL is pressend, give focus to text box.
					GameModule::Overlay::TheChat->setTypingMode();
				else if (Key == DIK_ESCAPE) // Escape is pressed, reset focus of text box.
					GameModule::Overlay::TheChat->setTypingMode(true);
				else if (Key == DIK_RETURN || Key == DIK_NUMPADENTER) // Enter is pressed, send the message and reset focus of text box.
				{
					GameModule::Overlay::TheChat->SendChatMessage();
					GameModule::Overlay::TheChat->setTypingMode(true);
				}
				else
				{
					GameModule::Overlay::TheGUI->InjectKey(Key, true);
				}
			}

			void UnmanagedInputListener::OnRelease(BYTE code)
			{
				unsigned char Key = code;

				GameModule::Overlay::TheGUI->InjectKey(Key, false);
			}

			void UnmanagedInputListener::OnMousePress(BYTE code)
			{
				GameModule::Overlay::TheGUI->InjectMouse((unsigned char)code, true);
			}

			void UnmanagedInputListener::OnMouseRelease(BYTE code)
			{
				GameModule::Overlay::TheGUI->InjectMouse((unsigned char)code, false);
			}

			void UnmanagedInputListener::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
			{
				GameModule::Overlay::TheGUI->MouseMove(x, y, z);
			}
		}
	}
}