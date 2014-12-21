#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <DirectX\DirectXHook.h>

namespace Logic
{
	namespace Overlay
	{
		class GUI
		{
			public:

			GUI();

			~GUI();

			MyGUI::Gui* getGUI();

			void OnRender(IDirect3DDevice9* pDevice);
			void OnLostDevice(IDirect3DDevice9* pDevice);

			void setCursor(bool Visible);

			void InjectKey(unsigned char key, bool isPressed);
			void InjectMouse(unsigned char Key, bool isPressed);
			void MouseMove(unsigned int PositionX, unsigned int PositionY, unsigned int PositionZ);

			private:

			MyGUI::DirectXPlatform* directXPlatform;
			MyGUI::Gui* myGUI;

			int PositionX, PositionY;
		};

		extern GUI* TheGUI;
	}
}
