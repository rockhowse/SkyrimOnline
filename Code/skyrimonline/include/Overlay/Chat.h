#pragma once

#include <stdafx.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

#include <Engine/Game.h>
#include <boost/thread/mutex.hpp>

class Chat
{
public:

	Chat(MyGUI::Gui* apGUI);

	~Chat();

	void SetVisible(bool aHide);

	void SetTyping(bool aForceHide = false);
	bool IsTyping() const;
	bool IsVisible() const;

	void AddChatMessage(const MyGUI::UString& acString);
	void SendChatMessage();
			
private:

	MyGUI::Gui* m_pGUI;
	MyGUI::EditBox* m_pList;
	MyGUI::EditBox* m_pEdit;

	// Server Connect
	MyGUI::EditBox* m_pAddr;
	MyGUI::EditBox* m_pPort;
	MyGUI::Button* m_pConnect;

	size_t m_scrollBarPosition[2];
			
	std::list<std::string> m_chatList; // To keep number of messages and text to get length of the first message.

	void EditKeyPressEvent(MyGUI::EditBox* aSender);

	void MouseClickedEvent(MyGUI::Widget* aSender); 

	/*	Mouse Event testing 
	void MousePressedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id);
	void MouseReleasedEvent(MyGUI::Widget* aSender, int left, int top, MyGUI::MouseButton id);
	static void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old);
	static void notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new);
	*/
};

extern Chat* TheChat;

