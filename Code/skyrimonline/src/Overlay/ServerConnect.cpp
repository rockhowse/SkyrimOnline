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

	//m_pAddr->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	//m_pPort->eventEditTextChange += MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);

	m_pConnect->eventMouseButtonClick += MyGUI::newDelegate(this, &ServerConnect::MouseClickedEvent);
	m_pConnect->eventMouseButtonPressed += MyGUI::newDelegate(this, &ServerConnect::MousePressedEvent);
	m_pConnect->eventMouseButtonReleased += MyGUI::newDelegate(this, &ServerConnect::MouseReleasedEvent);
	m_pConnect->eventMouseSetFocus += MyGUI::newDelegate(notifyMouseSetFocus);
	m_pConnect->eventMouseLostFocus += MyGUI::newDelegate(notifyMouseLostFocus);
}

ServerConnect::~ServerConnect()
{
	//m_pAddr->eventEditTextChange -= MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);
	//m_pPort->eventEditTextChange -= MyGUI::newDelegate(this, &ServerConnect::EditKeyPressEvent);

	m_pConnect->eventMouseButtonClick -= MyGUI::newDelegate(this, &ServerConnect::MouseClickedEvent);
	m_pConnect->eventMouseButtonPressed -= MyGUI::newDelegate(this, &ServerConnect::MousePressedEvent);
	m_pConnect->eventMouseButtonReleased -= MyGUI::newDelegate(this, &ServerConnect::MouseReleasedEvent);
	m_pConnect->eventMouseSetFocus -= MyGUI::newDelegate(notifyMouseSetFocus);
	m_pConnect->eventMouseLostFocus -= MyGUI::newDelegate(notifyMouseLostFocus);
}

void ServerConnect::SetVisible(bool aHide)
{
	if (m_pAddr == nullptr || m_pPort == nullptr || m_pConnect == nullptr)
		return;

	m_pAddr->setVisible(aHide);
	m_pPort->setVisible(aHide);
	m_pConnect->setVisible(aHide);
}

bool ServerConnect::IsVisible() const
{
	return m_pAddr->isVisible() && m_pPort->isVisible() && m_pConnect->isVisible();
}

void ServerConnect::MousePressedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id)
{
	MyGUI::Button* image = aSender->castType<MyGUI::Button>();
	image->setCaption("Pressed");
}

void ServerConnect::MouseReleasedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id)
{
	MyGUI::Button* image = aSender->castType<MyGUI::Button>();
	image->setCaption("Released");
}

void ServerConnect::MouseClickedEvent(MyGUI::Widget* aSender)
{
	MyGUI::Button* image = aSender->castType<MyGUI::Button>();
	image->setCaption("Clicked");
}

void ServerConnect::notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
{
	MyGUI::Button* image = _sender->castType<MyGUI::Button>();
	image->setCaption("Active");
}

void ServerConnect::notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
{
	MyGUI::Button* image = _sender->castType<MyGUI::Button>();
	image->setCaption("Normal");
}
