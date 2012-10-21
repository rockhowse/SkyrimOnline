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

			}
			//--------------------------------------------------------------------------------
			InGame::~InGame()
			{

			}
			//--------------------------------------------------------------------------------
			void InGame::OnEnter()
			{
				mChat->Show();

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
				mChat->Update(pDelta);
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
				os << "You just entered region 0x" << std::hex << SkyrimOnline::GetInstance().GetPlayerEntry().GetCharacter().GetLocationId();
				mChat->Log(os.str());
			}
			//--------------------------------------------------------------------------------
			void InGame::OnChatMessage(const std::string& pMessage)
			{
				Framework::Network::Packet packet(kClientChatMessage);
				packet << pMessage;
				TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerServer, packet);
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