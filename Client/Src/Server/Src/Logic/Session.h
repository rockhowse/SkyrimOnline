#pragma once

#include <Game/PlayerGOMEntry.h>
#include <Game/Player.hpp>

namespace Skyrim
{
	using namespace Framework::Network;

	namespace Logic
	{
		class Session : public ::Game::Player
		{
		public:

			Session(unsigned int id, ::Game::GameServer* server);
			~Session();

			static void Init();

			boost::signal<void(const std::string&)> OnChatMessage;

			std::string GetName();

		protected:

			void OnSynchronize();
			void OnEnterAwareness();

			void HandlePlayerMoveState(Network::Packet&);
			void HandleChatMessage(Network::Packet&);
			void HandleServiceResponse(Network::Packet&);
			void HandleMountState(Network::Packet&);
			void HandleInitialData(Network::Packet&);

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);

		private:

			std::string mName;
			Network::TcpConnection::pointer mConnection;
			std::vector<boost::signals::connection> mEventLinks;
			boost::shared_ptr<Game::ActorController> mController;
		};
	}
}