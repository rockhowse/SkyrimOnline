#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <Engine/Game.h>
#include <boost/thread/mutex.hpp>

namespace Logic
{
	namespace Overlay
	{
		class Chat
		{
		public:

			Chat(MyGUI::Gui* apGUI);

			~Chat();

			void SetVisibility(bool aForceHide);

			void SetTyping(bool aForceHide = false);
			bool IsTyping() const;
			void AddChatMessage(const MyGUI::UString& acString);
			void SendChatMessage();

		private:

			MyGUI::Gui* m_pGUI;
			MyGUI::ListPtr m_pList;
			MyGUI::EditBox* m_pEdit;
			boost::mutex m_lock;

		};

		extern Chat* TheChat;
	}
}
