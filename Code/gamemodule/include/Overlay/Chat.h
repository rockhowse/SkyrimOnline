#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

namespace GameModule
{
	namespace Overlay
	{
		class Chat
		{
			public:

			Chat(MyGUI::Gui* pUI);

			~Chat();

			void setTypingMode(bool AllowTyping);

			private:

			MyGUI::Gui* myGUI;
			MyGUI::ListPtr myList;
			MyGUI::EditPtr myEdit;

			HANDLE mMutex;

		};

		extern Chat* TheChat;
	}
}
