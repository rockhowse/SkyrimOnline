#include <Engine\Input.h>
#include <DInput\Input.hpp>

namespace Logic
{
	namespace Engine
	{
		namespace Input
		{
			InputListener* TheInputManager = nullptr;

			void InputManager::OnPress(BYTE code)
			{
				uint8_t key = code;

				if (MyGUI::InputManager::getInstance().isFocusKey() == false && key == DIK_RCONTROL) // Right CTRL is pressend, give focus to text box.
				{
					Logic::Overlay::TheChat->SetTyping(false);
					TheIInputHook->SetInputEnabled(false);
				}
				else if (key == DIK_ESCAPE) // Escape is pressed, reset focus of text box.
				{
					Logic::Overlay::TheChat->SetTyping(true);
					TheIInputHook->SetInputEnabled(true);
				}
				else if ((key == DIK_RETURN || key == DIK_NUMPADENTER) && Logic::Overlay::TheChat->IsTyping()) // Enter is pressed, send the message and reset focus of text box.
				{
					Logic::Overlay::TheChat->SendChatMessage();
					Logic::Overlay::TheChat->SetTyping(true);
				}
				else if (key != DIK_RCONTROL && key != DIK_LCONTROL)
				{
					Logic::Overlay::TheGUI->InjectKey(key, true);
				}
			}

			void InputManager::OnRelease(BYTE code)
			{
				uint8_t key = code;
				if (key != DIK_RCONTROL && key != DIK_LCONTROL)
				{
					Logic::Overlay::TheGUI->InjectKey(key, false);
				}
			}

			void InputManager::OnMousePress(BYTE code)
			{
				Logic::Overlay::TheGUI->InjectMouse((uint8_t)code, true);
			}

			void InputManager::OnMouseRelease(BYTE code)
			{
				Logic::Overlay::TheGUI->InjectMouse((uint8_t)code, false);
			}

			void InputManager::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
			{
				Logic::Overlay::TheGUI->MouseMove(x, y, z);
			}
		}
	}
}