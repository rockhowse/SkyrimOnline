#include <Overlay\Chat.h>
#include <MyGUI_Precompiled.h>


Chat* TheChat = nullptr;

Chat::Chat(MyGUI::Gui* pUI)
	: m_pGUI(pUI)
{
	MyGUI::LayoutManager::getInstance().loadLayout("Chat.xml");

	m_pEdit = m_pGUI->findWidget<MyGUI::EditBox>("Chat_Edit");
	m_pList = m_pGUI->findWidget<MyGUI::EditBox>("Chat_List");

	//MyGUI::LayoutManager::getInstance().loadLayout("ServerConnect.xml");

	m_pAddr = m_pGUI->findWidget<MyGUI::EditBox>("Server_Edit_Addr");
	m_pPort = m_pGUI->findWidget<MyGUI::EditBox>("Server_Edit_Port");
	m_pConnect = m_pGUI->findWidget<MyGUI::Button>("Server_Btn_Connect");

	m_pList->setTextAlign(MyGUI::Align::Default);
	m_pList->setEditStatic(true);
	m_pList->setVisibleHScroll(false);
	m_pList->setVisibleVScroll(true);
	m_pList->setOverflowToTheLeft(true);
	m_pList->setEditWordWrap(true);

	m_pEdit->eventEditTextChange += MyGUI::newDelegate(this, &Chat::EditKeyPressEvent);

	//m_pAddr->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	//m_pPort->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);

	m_pAddr->setCaption("127.0.0.1");
	m_pPort->setCaption("10578");

	m_pConnect->eventMouseButtonClick += MyGUI::newDelegate(this, &Chat::MouseClickedEvent);

	/*	
	m_pConnect->eventMouseButtonPressed += MyGUI::newDelegate(this, &Chat::MousePressedEvent);
	m_pConnect->eventMouseButtonReleased += MyGUI::newDelegate(this, &Chat::MouseReleasedEvent);
	m_pConnect->eventMouseSetFocus += MyGUI::newDelegate(notifyMouseSetFocus);
	m_pConnect->eventMouseLostFocus += MyGUI::newDelegate(notifyMouseLostFocus);
	*/

}

Chat::~Chat()
{
	m_pEdit->eventEditTextChange -= MyGUI::newDelegate(this, &Chat::EditKeyPressEvent);

	m_pConnect->eventMouseButtonClick -= MyGUI::newDelegate(this, &Chat::MouseClickedEvent);

	/*
	m_pConnect->eventMouseButtonPressed -= MyGUI::newDelegate(this, &ServerConnect::MousePressedEvent);
	m_pConnect->eventMouseButtonReleased -= MyGUI::newDelegate(this, &ServerConnect::MouseReleasedEvent);
	m_pConnect->eventMouseSetFocus -= MyGUI::newDelegate(notifyMouseSetFocus);
	m_pConnect->eventMouseLostFocus -= MyGUI::newDelegate(notifyMouseLostFocus);
	*/
}

void Chat::SetVisible(bool aHide)
{
	if (m_pEdit == nullptr || m_pList == nullptr)
		return;
	m_pEdit->setVisible(aHide);
	m_pList->setVisible(aHide);

	/**/
	if (m_pAddr == nullptr || m_pPort == nullptr || m_pConnect == nullptr)
		return;

	m_pAddr->setVisible(aHide);
	
	m_pPort->setVisible(aHide);
	m_pConnect->setVisible(aHide);
}

void Chat::SetTyping(bool aForceHide)
{
	if (aForceHide == false && MyGUI::InputManager::getInstance().isFocusKey() == false)
	{
		TheController->DisableInput();
		TheGUI->SetCursor(true);
		MyGUI::InputManager::getInstance().setKeyFocusWidget(m_pEdit);
	}
	else
	{
		TheController->EnableInput();
		TheGUI->SetCursor(false);
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
	m_scrollBarPosition[0] = m_pList->getVScrollRange();
	m_scrollBarPosition[1] = m_pList->getVScrollPosition();

	m_pList->insertText(acString + '\n');
	m_chatList.push_back(acString + '\n');

	if (m_pList->getVScrollPosition() - m_scrollBarPosition[1] > m_pList->getVScrollRange() - m_scrollBarPosition[0])
		m_pList->setVScrollPosition(m_scrollBarPosition[1]);

	if (m_chatList.size() > 200)
	{
		m_pList->eraseText(0, m_chatList.front().length());
		m_chatList.erase(m_chatList.begin());
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
	TheController->SendReliable(pMessage);

	m_pEdit->eraseText(0, m_pEdit->getTextLength());
}

void Chat::EditKeyPressEvent(MyGUI::EditBox* aSender)
{
	if (aSender->getTextLength() > 256)
		aSender->eraseText(aSender->getTextLength() - 1, 1);
}

void Chat::MouseClickedEvent(MyGUI::Widget* aSender)
{
	/*	
	MyGUI::Button* image = aSender->castType<MyGUI::Button>();
	image->setCaption("Clicked");
	*/
	uint16_t port = atoi((char *) m_pPort->getCaption().asUTF8_c_str());

	if (port > 0) {
		TheController->ConnectToWorld((char *)m_pAddr->getCaption().asUTF8_c_str(), port);
	}
}

/* Mouse Event testing
void Chat::MouseReleasedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id)
{
	MyGUI::Button* image = aSender->castType<MyGUI::Button>();
	image->setCaption("Released");
}

void Chat::MousePressedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id)
{
MyGUI::Button* image = aSender->castType<MyGUI::Button>();
image->setCaption("Pressed");
}

void Chat::notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
{
	//MyGUI::Button* image = _sender->castType<MyGUI::Button>();
	//image->setCaption("Active");
}

void Chat::notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
{
	//MyGUI::Button* image = _sender->castType<MyGUI::Button>();
	//image->setCaption("Normal");
}
*/