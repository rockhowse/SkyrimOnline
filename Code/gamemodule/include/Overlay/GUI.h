#pragma once

#include <Engine\Game.h>
#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

namespace Game
{
	namespace Overlay
	{
		class GUI
		{
			public:

			GUI();

			~GUI();

			MyGUI::Gui* getGUI();

			private:

			MyGUI::DirectXPlatform* directXPlatform;
			MyGUI::Gui* myGUI;

		};
	}
}
