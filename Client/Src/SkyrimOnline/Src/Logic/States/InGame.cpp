#include <stdafx.h>
#include <Logic/States/InGame.hpp>
#include <SkyrimOnline.h>

#include <Game/MassiveMessageManager.hpp>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			//--------------------------------------------------------------------------------
			InGame::InGame()
			{
				mChat = boost::make_shared<Overlay::Chat>(SkyrimOnline::GetInstance().GetInterface().GetGui());
				mChat->Hide();

				mFriendList = boost::make_shared<Overlay::FriendList>(SkyrimOnline::GetInstance().GetInterface().GetGui());
				mFriendList->Hide();

				mChat->OnSendChatMessage.connect(boost::bind(&InGame::OnChatMessage, this, _1));
				SkyrimOnline::GetInstance().GetPlayerWatcher().OnRegion.connect(boost::bind(&InGame::OnEnterRegion, this, _1));

			}
			//--------------------------------------------------------------------------------
			InGame::~InGame()
			{

			}
			//--------------------------------------------------------------------------------
			void InGame::OnEnter()
			{
				mChat->Show();
				//mFriendList->Show();

				SkyrimOnline::GetInstance().SetMode(true);
			}
			//--------------------------------------------------------------------------------
			void InGame::OnLeave()
			{
				mChat->Hide();
				mFriendList->Hide();
			}
			//--------------------------------------------------------------------------------
			void InGame::OnUpdate(uint32_t pDelta)
			{
				//if(TheMassiveMessageMgr->IsOnline())
				{
					SkyrimOnline::GetInstance().GetPlayerWatcher().Update(pDelta);
				}

				mChat->Update(pDelta);

				SkyrimOnline::GetInstance().GetControllerManager().Update(pDelta);
			}
			//--------------------------------------------------------------------------------
			bool InGame::IsSwitchingAllowed()
			{
				return true;
			}
			//--------------------------------------------------------------------------------
			void InGame::OnEnterRegion(uint32_t pRegion)
			{
				std::ostringstream os;
				os << "You just entered region 0x" << std::hex << SkyrimOnline::GetInstance().GetPlayerWatcher().GetCharacter().GetLocationId();
				mChat->Log(os.str());
			}
			//--------------------------------------------------------------------------------
			void InGame::OnChatMessage(const std::string& pMessage)
			{
				Framework::Network::Packet packet(kClientChatMessage);
				packet << pMessage;
				TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerServer, packet);

				//mChat->Log("You are not connected !","#FF0000");
				
			}
			//--------------------------------------------------------------------------------
			void InGame::OnRemoteChatMessage(const std::string& pMessage)
			{
				mChat->Log(pMessage,"#FFBF00");
			}
			//--------------------------------------------------------------------------------
			void InGame::OnRemoteSpawn()
			{
				mChat->Log("Spawned a player");
			}
			//--------------------------------------------------------------------------------
		}
	}
}