#include <Overlay\Chat.h>
#include <MyGUI_Precompiled.h>

namespace GameModule
{
	namespace Overlay
	{
		Chat* TheChat = nullptr;

		Chat::Chat(MyGUI::Gui* pUI) : myGUI(pUI)
		{
			MyGUI::LayoutManager::getInstance().loadLayout("Chat.xml");

			myEdit = myGUI->findWidget<MyGUI::EditBox>("Chat_Edit");
			myList = myGUI->findWidget<MyGUI::List>("Chat_List");

			myList->setNeedKeyFocus(false);
			myEdit->setEditMultiLine(false);

			mMutex = CreateMutex(NULL, FALSE, NULL);
		}

		Chat::~Chat()
		{

		}

		void Chat::setTypingMode(bool ForceHide)
		{
			if (ForceHide == false && MyGUI::InputManager::getInstance().isFocusKey() == false)
			{
				GameModule::Engine::iController->DisableInput();
				GameModule::Overlay::TheGUI->setCursor(true);
				MyGUI::InputManager::getInstance().setKeyFocusWidget(myEdit);
			}
			else
			{
				GameModule::Engine::iController->EnableInput();
				GameModule::Overlay::TheGUI->setCursor(false);
				MyGUI::InputManager::getInstance().resetKeyFocusWidget();
			}
		}

		void Chat::AddChatMessage(const MyGUI::UString& Text)
		{
			myList->addItem(Text); // this line should be: "Username says: text" but for the moment it is good.
		}

		void Chat::SendChatMessage()
		{
			myList->addItem(myEdit->getCaption()); // this line should be: "Username says: text" but for the moment it is good.
			myEdit->eraseText(0, myEdit->getTextLength());
		}
	}
}