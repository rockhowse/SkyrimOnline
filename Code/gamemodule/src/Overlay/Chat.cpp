#include <Overlay\Chat.h>

namespace GameModule
{
	namespace Overlay
	{
		Chat* TheChat = nullptr;

		Chat::Chat(MyGUI::Gui* pUI) : myGUI(pUI)
		{
			MyGUI::LayoutManager::getInstance().loadLayout("Chat.xml");

			myEdit = myGUI->findWidget<MyGUI::Edit>("Chat_Edit");
			myList = myGUI->findWidget<MyGUI::List>("Chat_List");

			myList->setNeedKeyFocus(false);
			mMutex = CreateMutex(NULL, FALSE, NULL);
		}

		Chat::~Chat()
		{

		}

		void Chat::setTypingMode(bool AllowTyping)
		{
			if (AllowTyping == true && MyGUI::InputManager::getInstance().isFocusKey() == false)
				MyGUI::InputManager::getInstance().setKeyFocusWidget(myGUI->findWidget<MyGUI::Edit>("Chat_Edit"));
			else if (AllowTyping == false && MyGUI::InputManager::getInstance().isFocusKey() == true)
				MyGUI::InputManager::getInstance().resetKeyFocusWidget();
		}
	}
}