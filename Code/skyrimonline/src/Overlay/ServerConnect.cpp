#include <Overlay\ServerConnect.h>
#include <MyGUI_Precompiled.h>


ServerConnect* TheServerConnect = nullptr;

ServerConnect::ServerConnect(MyGUI::Gui* pUI)
	: m_pGUI(pUI)
{
	MyGUI::LayoutManager::getInstance().loadLayout("ServerConnect.xml");

	m_pAddr		= m_pGUI->findWidget<MyGUI::EditBox>("Server_Edit_Addr");
	m_pPort		= m_pGUI->findWidget<MyGUI::EditBox>("Server_Edit_Port");
	m_pConnect	= m_pGUI->findWidget<MyGUI::Button>("Server_Btn_Connect");

	m_pAddr->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	m_pPort->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	m_pConnect->eventMouseButtonClick += MyGUI::newDelegate(this, &ServerConnect::ButtonClickEvent);
}

ServerConnect::~ServerConnect()
{
	m_pAddr->eventEditTextChange -= MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	m_pPort->eventEditTextChange -= MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);

	m_pConnect->eventMouseButtonClick -= MyGUI::newDelegate(this, &ServerConnect::ButtonClickEvent);
}

void ServerConnect::SetVisible(bool aHide)
{
	if (m_pAddr == nullptr || m_pPort == nullptr || m_pConnect == nullptr)
		return;

	m_pAddr->setVisible(aHide);
	m_pPort->setVisible(aHide);
	m_pConnect->setVisible(aHide);
}

void ServerConnect::SetTyping(bool aForceHide)
{
	if (aForceHide == false && MyGUI::InputManager::getInstance().isFocusKey() == false)
	{
		TheController->DisableInput();
		TheGUI->SetCursor(true);
		MyGUI::InputManager::getInstance().setKeyFocusWidget(m_pAddr);
	}
	else
	{
		TheController->EnableInput();
		TheGUI->SetCursor(false);
		MyGUI::InputManager::getInstance().resetKeyFocusWidget();
	}
}

bool ServerConnect::IsTyping() const
{
	return MyGUI::InputManager::getInstance().isFocusKey();
}

bool ServerConnect::IsVisible() const
{
	return m_pAddr->isVisible() && m_pPort->isVisible() && m_pConnect->isVisible();
}

void ServerConnect::AddServerConnectMessage(const MyGUI::UString& acString)
{
	/*
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
	*/
}

void ServerConnect::SendServerConnectMessage()
{
	/*
	if (m_pEdit->getTextLength() == 0)
	{
		return;
	}

	Messages::CliGame_ServerConnectSend* pMessage = new Messages::CliGame_ServerConnectSend;

	pMessage->message = m_pEdit->getCaption();
	TheController->SendReliable(pMessage);

	m_pEdit->eraseText(0, m_pEdit->getTextLength());
	*/
}

void ServerConnect::EditKeyPressEvent(MyGUI::EditBox* aSender)
{
	if (aSender->getTextLength() > 256)
		aSender->eraseText(aSender->getTextLength() - 1, 1);
}

void ServerConnect::ButtonClickEvent(MyGUI::Widget* aSender)
{
	// connect to server here
}
