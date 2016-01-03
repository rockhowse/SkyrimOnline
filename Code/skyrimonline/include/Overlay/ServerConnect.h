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

	void AddServerConnectMessage(const MyGUI::UString& acString);
	void SendServerConnectMessage();
			
private:

	MyGUI::Gui* m_pGUI;
	MyGUI::EditBox* m_pAddr;
	MyGUI::EditBox* m_pPort;
	MyGUI::Button* m_pConnect;

	void EditKeyPressEvent(MyGUI::EditBox* aSender);
	void ButtonClickEvent(MyGUI::Widget* aSender);
};

extern ServerConnect* TheServerConnect;

