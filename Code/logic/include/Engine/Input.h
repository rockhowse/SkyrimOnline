#pragma once

#include <stdafx.h>

#include <Overlay\GUI.h>
#include <Overlay\Chat.h>

namespace Logic
{
	namespace Engine
	{
		namespace Input
		{
			struct InputManager : public InputListener
			{
				virtual void OnPress(BYTE code);
				virtual void OnRelease(BYTE code);
				virtual void OnMousePress(BYTE code);
				virtual void OnMouseRelease(BYTE code);
				virtual void OnMouseMove(unsigned int x, unsigned int y, unsigned int z);
			};

			extern InputListener* TheInputManager;
		}
	}
}