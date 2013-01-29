//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "ShardList.h"
#include <GameWorld.h>
#include <Logic/Session.h>


namespace Skyrim
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		ShardList::ShardList(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			float halfHeight(mUI->getViewHeight() * 0.5);

			//Public IP
			/*mPublicIP = mUI->createWidget<MyGUI::StaticText>("StaticText",
				mUI->getViewWidth() * 0.4, halfHeight - 73,
				mUI->getViewWidth() * 0.2, 26,
				MyGUI::Align::Left, "Overlapped",
				"ShardPublicIPText");

			mPublicIP->setCaption("Public IP : Resolving");*/

			//Framework::Network::HttpClient::AsyncRequest(boost::bind(&ShardList::OnResolveIP, this, _1), TheMassiveMessageMgr->GetIoServicePool().GetIoService(), "automation.whatismyip.com", "/n09230945.asp");

			//char hostBuf[1024];
			//gethostname(hostBuf, 1024),

			//Local IP
			/*mLocalIP = mUI->createWidget<MyGUI::StaticText>("StaticText",
				mUI->getViewWidth() * 0.4, halfHeight - 53,
				mUI->getViewWidth() * 0.2, 26,
				MyGUI::Align::Left, "Overlapped",
				"ShardLocalIPText");

			std::string strAddresses("");
			struct hostent *eHost = gethostbyname(hostBuf);
			if(eHost != 0)
			{
				for(int i(0); eHost->h_addr_list[i] != 0; ++i)
				{
					struct in_addr address;
					memcpy(&address, eHost->h_addr_list[i], sizeof(struct in_addr));

					if(strAddresses.empty())
					{
						strAddresses = (std::string(inet_ntoa(address)));
					}
					else
					{
						strAddresses += " | " + (std::string(inet_ntoa(address)));
					}
				}
			}
			else
			{
				strAddresses = "127.0.0.1";
			}

			mLocalIP->setCaption("Local IP Addresses: " + strAddresses);*/

			//Server Address
			mText = mUI->createWidget<MyGUI::StaticText>("StaticText",
				mUI->getViewWidth() * 0.4, halfHeight - 23,
				mUI->getViewWidth() * 0.2, 26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListText");
			mText->setCaption("Server address : ");

			//List IP
			mEdit = mUI->createWidget<MyGUI::Edit>("Edit",
				mUI->getViewWidth() * 0.4, halfHeight - 3,
				mUI->getViewWidth() * 0.2, 26,
				MyGUI::Align::Default, "Overlapped", "ShardListIp");

			//Join Button
			mButton = mUI->createWidget<MyGUI::Button>("Button",
				mUI->getViewWidth() * 0.4, halfHeight + 23,
				mUI->getViewWidth()*0.10 - 10, 26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListButton");
			mButton->setCaption("Join");

			//Host Button
			/*mHostButton = mUI->createWidget<MyGUI::Button>("Button",
				mUI->getViewWidth()*0.5 + 10, halfHeight + 23,
				mUI->getViewWidth()*0.10 - 10, 26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListHostButton");
			mHostButton->setCaption("Host");*/

			mButton->eventMouseButtonClick = MyGUI::newDelegate(this, &ShardList::Handle_Click);
			//mHostButton->eventMouseButtonClick = MyGUI::newDelegate(this, &ShardList::Handle_HostClick);

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
			//mPublicIP->setVisible(v);
			//mLocalIP->setVisible(v);
			mEdit->setVisible(v);
			mText->setVisible(v);
			mButton->setVisible(v);
			//mHostButton->setVisible(v);

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
		void ShardList::OnResolveIP(const std::string& pData)
		{
			//mPublicIP->setCaption(std::string("Public IP : ") + pData.substr(3));
		}
		//--------------------------------------------------------------------------------
	}
}