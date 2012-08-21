#pragma once

#include <Overlay/Chat.h>
#include <Overlay/FriendList.h>
#include <Logic/GameState.hpp>
#include <Game/RemotePlayer.h>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			class InGame : public GameState
			{
			public:
				InGame();
				virtual ~InGame();

				void OnEnter();
				void OnLeave();
				void OnUpdate(uint32_t pDelta);

				// Gameplay
				void OnEnterRegion(uint32_t pRegion);

				// UI events
				void OnChatMessage(const std::string& pMessage);
					
				// Network
				void OnRemoteChatMessage(const std::string& pMessage);
				void OnRemoteSpawn();

				bool IsSwitchingAllowed();

				uint32_t GetId()
				{
					return 'inga';
				}

			private:

				boost::shared_ptr<Overlay::Chat> mChat;
				boost::shared_ptr<Overlay::FriendList> mFriendList;
			};
		}
	}
}