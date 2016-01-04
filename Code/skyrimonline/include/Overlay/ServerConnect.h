#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <Engine/Game.h>
#include <boost/thread/mutex.hpp>

class ServerConnect
{
public:

	ServerConnect(MyGUI::Gui* apGUI);

	~ServerConnect();

	void SetVisible(bool aHide);

	void SetTyping(bool aForceHide = false);
	bool IsTyping() const;
	bool IsVisible() const;
	
private:

	MyGUI::Gui* m_pGUI;
	MyGUI::EditBox* m_pAddr;
	MyGUI::EditBox* m_pPort;
	MyGUI::Button* m_pConnect;

	void MousePressedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id);
	void MouseReleasedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id);
	void MouseClickedEvent(MyGUI::Widget* aSender);
	static void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
	static void notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new);
};

extern ServerConnect* TheServerConnect;

