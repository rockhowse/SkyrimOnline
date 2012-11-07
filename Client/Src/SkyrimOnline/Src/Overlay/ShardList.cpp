//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "ShardList.h"
#include <GameWorld.h>
#include <Logic/Session.h>
#include <Network/Packet.h>

namespace Skyrim
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		ShardList::ShardList(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			mText = mUI->createWidget<MyGUI::StaticText>("StaticText", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2-43,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListText");
			mText->setCaption("Server address : ");

			mEdit = mUI->createWidget<MyGUI::Edit>("Edit", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2-13,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped", "ShardListIp");

			mButton = mUI->createWidget<MyGUI::Button>("Button",
				mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2 + 23,
				mUI->getViewWidth()*0.10 - 10,
				26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListButton");
			mButton->setCaption("Join");

			mHostButton = mUI->createWidget<MyGUI::Button>("Button",
				mUI->getViewWidth()*0.5 + 10,
				mUI->getViewHeight()/2 + 23,
				mUI->getViewWidth()*0.10 - 10,
				26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListHostButton");
			mHostButton->setCaption("Host");

			mButton->eventMouseButtonClick = MyGUI::newDelegate(this, &ShardList::Handle_Click);
			mHostButton->eventMouseButtonClick = MyGUI::newDelegate(this, &ShardList::Handle_HostClick);

			mEdit->setInheritsAlpha(true);
		}
		//--------------------------------------------------------------------------------
		ShardList::~ShardList()
		{
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Hide()
		{
			SetVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Show()
		{
			SetVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	ShardList::SetVisible(bool v)
		{
			mEdit->setVisible(v);
			mText->setVisible(v);
			mButton->setVisible(v);
			mHostButton->setVisible(v);
		}
		//--------------------------------------------------------------------------------
		bool	ShardList::IsVisible()
		{
			return mEdit->isVisible();
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Update(double e)
		{
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			OnShardPick(mEdit->getOnlyText().asUTF8());
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Handle_HostClick(MyGUI::WidgetPtr _widget)
		{
			OnHost();
		}
		//--------------------------------------------------------------------------------
	}
}