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
			m_pList = m_pGUI->findWidget<MyGUI::EditBox>("Chat_List");

			m_pList->setTextAlign(MyGUI::Align::Default);
			m_pList->setEditStatic(true);
			m_pList->setVisibleHScroll(false);
			m_pList->setVisibleVScroll(true);
			m_pList->setOverflowToTheLeft(true);
			m_pList->setEditWordWrap(true);

			m_pEdit->eventEditTextChange += MyGUI::newDelegate(this, &Chat::EditKeyPressEvent);
		}

		Chat::~Chat()
		{
			m_pEdit->eventEditTextChange -= MyGUI::newDelegate(this, &Chat::EditKeyPressEvent);
		}

		void Chat::SetVisible(bool aHide)
		{
			if (m_pEdit == nullptr || m_pList == nullptr)
				return;

			m_pEdit->setVisible(aHide);
			m_pList->setVisible(aHide);
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

		bool Chat::IsVisible() const
		{
			return m_pEdit->isVisible() && m_pList->isVisible();
		}

		void Chat::AddChatMessage(const MyGUI::UString& acString)
		{
			m_ScrollBarPosition[0] = m_pList->getVScrollRange();
			m_ScrollBarPosition[1] = m_pList->getVScrollPosition();

			m_pList->insertText(acString + '\n');
			m_ChatTextList.push_back(acString + '\n');

			if (m_pList->getVScrollPosition() - m_ScrollBarPosition[1] > m_pList->getVScrollRange() - m_ScrollBarPosition[0])
				m_pList->setVScrollPosition(m_ScrollBarPosition[1]);

			if (m_ChatTextList.size() > 200)
			{
				m_pList->eraseText(0, m_ChatTextList.front().length());
				m_ChatTextList.erase(m_ChatTextList.begin());
			}
		}

		void Chat::SendChatMessage()
		{
			if (m_pEdit->getTextLength() == 0)
			{
				return;
			}

			Messages::CliGame_ChatSend* pMessage = new Messages::CliGame_ChatSend;

			pMessage->message = m_pEdit->getCaption();
			Logic::Engine::TheController->SendReliable(pMessage);

			m_pEdit->eraseText(0, m_pEdit->getTextLength());
		}

		void Chat::EditKeyPressEvent(MyGUI::EditBox* aSender)
		{
			if (aSender->getTextLength() > 256)
				aSender->eraseText(aSender->getTextLength() - 1, 1);
		}
	}
}