#include <stdafx.h>
#include <Overlay\GUI.h>

namespace Game
{
	namespace Overlay
	{

		GUI::GUI() : directXPlatform(nullptr), myGUI(nullptr)
		{

		}

		GUI::~GUI()
		{

		}

		MyGUI::Gui* GUI::getGUI()
		{
			return myGUI;
		}
	}
}