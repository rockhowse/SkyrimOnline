#include <stdafx.h>
#include <Logic/Session.h>
#include <Logic/States/InGame.hpp>
#include <GameWorld.h>

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
				mChat = boost::make_shared<Overlay::Chat>(Overlay::TheSystem->GetGui());
				mChat->Hide();

				mFriendList = boost::make_shared<Overlay::FriendList>(Overlay::TheSystem->GetGui());
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

				auto session = reinterpret_cast<Logic::Session*>(TheMassiveMessageMgr->GetLocalPlayer());
				session->OnChatMessage.connect(boost::bind(&InGame::OnRemoteChatMessage, this, _1));
				TheGameWorld->SetMode(true);
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
				os << "You just entered region 0x" << std::hex << TheMassiveMessageMgr->GetLocalPlayer();
				mChat->Log(os.str());
			}
			//--------------------------------------------------------------------------------
			void InGame::OnChatMessage(const std::string& pMessage)
			{
				Framework::Network::Packet packet(kClientChatMessage);
				std::ostringstream os;

				os << std::string("[") << TheGameWorld->GetUser() << std::string("] : ") << pMessage;

				packet << os.str();
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