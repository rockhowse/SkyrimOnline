#include <Overlay\Chat.h>
#include <MyGUI_Precompiled.h>

namespace Logic
{
	namespace Overlay
	{
		Chat* TheChat = nullptr;

		Chat::Chat(MyGUI::Gui* pUI) 
			: m_pGUI(pUI)
		{
			MyGUI::LayoutManager::getInstance().loadLayout("Chat.xml");

			m_pEdit = m_pGUI->findWidget<MyGUI::EditBox>("Chat_Edit");
			m_pList = m_pGUI->findWidget<MyGUI::List>("Chat_List");

			m_pList->setNeedKeyFocus(false);
			m_pEdit->setEditMultiLine(false);
		}

		Chat::~Chat()
		{

		}

		void Chat::SetVisibility(bool aForceHide)
		{
			if (m_pEdit == nullptr || m_pList == nullptr)
				return;

			if (aForceHide == false && m_pEdit->isVisible() == false && m_pList->isVisible() == false)
			{
				m_pEdit->setVisible(true);
				m_pList->setVisible(true);
			}
			else
			{
				m_pEdit->setVisible(false);
				m_pList->setVisible(false);
			}
		}

		void Chat::SetTyping(bool aForceHide)
		{
			if (aForceHide == false && MyGUI::InputManager::getInstance().isFocusKey() == false)
			{
				Logic::Engine::TheController->DisableInput();
				Logic::Overlay::TheGUI->SetCursor(true);
				MyGUI::InputManager::getInstance().setKeyFocusWidget(m_pEdit);
			}
			else
			{
				Logic::Engine::TheController->EnableInput();
				Logic::Overlay::TheGUI->SetCursor(false);
				MyGUI::InputManager::getInstance().resetKeyFocusWidget();
			}
		}

		bool Chat::IsTyping() const
		{
			return MyGUI::InputManager::getInstance().isFocusKey();
		}

		void Chat::AddChatMessage(const MyGUI::UString& acString)
		{
			m_pList->addItem(acString);
		}

		void Chat::SendChatMessage()
		{
			Messages::CliGame_ChatSend* pMessage = new Messages::CliGame_ChatSend;

			pMessage->message = m_pEdit->getCaption();
			Logic::Engine::TheController->SendReliable(pMessage);

			m_pEdit->eraseText(0, m_pEdit->getTextLength());
		}
	}
}