#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <DirectX\DirectXHook.h>

namespace GameModule
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

			private:

			MyGUI::DirectXPlatform* directXPlatform;
			MyGUI::Gui* myGUI;

		};

		extern GUI* TheGUI;
	}
}
