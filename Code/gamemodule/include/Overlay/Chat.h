#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <Engine\Game.h>

namespace GameModule
{
	namespace Overlay
	{
		class Chat
		{
			public:

			Chat(MyGUI::Gui* pUI);

			~Chat();

			void setTypingMode(bool ForceHide = false);
			void AddChatMessage(const MyGUI::UString& Text);
			void SendChatMessage();

			private:

			MyGUI::Gui* myGUI;
			MyGUI::ListPtr myList;
			MyGUI::EditBox* myEdit;

			HANDLE mMutex;

		};

		extern Chat* TheChat;
	}
}
