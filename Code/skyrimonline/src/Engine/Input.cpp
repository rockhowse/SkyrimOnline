#include <Engine\Input.h>
#include <DInput\Input.hpp>

InputListener* TheInputManager = nullptr;

void InputManager::OnPress(BYTE code)
{
	uint8_t key = code;

	if (MyGUI::InputManager::getInstance().isFocusKey() == false && key == DIK_RCONTROL) // Right CTRL is pressend, give focus to text box.
	{
		TheChat->SetTyping(false);
		TheIInputHook->SetInputEnabled(false);
	}
	else if (key == DIK_ESCAPE) // Escape is pressed, reset focus of text box.
	{
		TheChat->SetTyping(true);
		TheIInputHook->SetInputEnabled(true);
	}
	else if ((key == DIK_RETURN || key == DIK_NUMPADENTER) && TheChat->IsTyping()) // Enter is pressed, send the message and reset focus of text box.
	{
		TheChat->SendChatMessage();
		TheChat->SetTyping(true);
		TheIInputHook->SetInputEnabled(true);
	}
	else if (key == DIK_F8)
	{
		TheChat->SetVisible(!TheChat->IsVisible());
	}
	else if (key != DIK_RCONTROL && key != DIK_LCONTROL)
	{
		TheGUI->InjectKey(key, true);
	}

	if (TheIInputHook->IsInputEnabled())
	{

	}
}

void InputManager::OnRelease(BYTE code)
{
	uint8_t key = code;
	if (key != DIK_RCONTROL && key != DIK_LCONTROL)
	{
		TheGUI->InjectKey(key, false);
	}
}

void InputManager::OnMousePress(BYTE code)
{
	TheGUI->InjectMouse((uint8_t)code, true);
}

void InputManager::OnMouseRelease(BYTE code)
{
	TheGUI->InjectMouse((uint8_t)code, false);
}

void InputManager::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
{
	TheGUI->MouseMove(x, y, z);
}
