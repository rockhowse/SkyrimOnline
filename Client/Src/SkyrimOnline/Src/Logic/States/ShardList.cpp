#include <stdafx.h>
#include <Logic/States/ShardList.hpp>
#include <GameWorld.h>
#include <Overlay/Message.h>

#include <Game/MassiveMessageManager.hpp>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			//--------------------------------------------------------------------------------
			ShardList::ShardList()
			{
				mShardList = boost::make_shared<Overlay::ShardList>(Overlay::TheSystem->GetGui());
				mShardList->Hide();
				mShardList->OnHost.connect(boost::bind(&ShardList::OnHost, this));
				mShardList->OnShardPick.connect(boost::bind(&ShardList::OnShardPick, this, _1));

				TheMassiveMessageMgr->OnConnection.connect(boost::bind(&ShardList::OnConnect, this, _1));
			}
			//--------------------------------------------------------------------------------
			ShardList::~ShardList()
			{

			}
			//--------------------------------------------------------------------------------
			void ShardList::OnEnter()
			{
				TheGameWorld->SetMode(false);
				mShardList->Show();
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnLeave()
			{
				mShardList->Hide();
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnUpdate(uint32_t pDelta)
			{
				::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
				::Game::SetInChargen(true, true, false);

				mShardList->Update(0.0);
				Overlay::TheSystem->SetCursor(true);
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnShardPick(const std::string& pShard)
			{
				System::Log::Debug(std::string("Shard picked : ") + pShard);
				/*Overlay::TheMessage->SetCaption("Joining is disabled for now !");
				Overlay::TheMessage->Show();*/

				mShardList->Hide();

				Overlay::TheMessage->SetCaption("Connecting...");
				Overlay::TheMessage->SetVisible(true);

				TheMassiveMessageMgr->SetAddress(pShard);
				TheMassiveMessageMgr->SetPort(kGamePort);
				TheMassiveMessageMgr->BeginMultiplayer(false);
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnHost()
			{
				System::Log::Debug("Hosting a server...");

				TheMassiveMessageMgr->SetPort(kGamePort);
				TheMassiveMessageMgr->BeginMultiplayer(true);

				TheGameWorld->SetState("InGame");
			}
			//--------------------------------------------------------------------------------
			void ShardList::OnConnect(bool pConnected)
			{
				if(!pConnected)
				{
					Overlay::TheMessage->SetCaption("Failed to connect...");
					Overlay::TheMessage->SetVisible(true);
					mShardList->Show();
				}
				else
				{
					Overlay::TheMessage->SetVisible(false);
					TheGameWorld->SetState("InGame");
				}
			}
			//--------------------------------------------------------------------------------
			bool ShardList::IsSwitchingAllowed()
			{
				return false;
			}
			//--------------------------------------------------------------------------------
		}
	}
}