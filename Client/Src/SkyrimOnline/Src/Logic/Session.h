#pragma once

#include <Game/PlayerEntry.h>
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
			boost::signal<void()>					OnSpawn;

		protected:

			void HandlePlayerSpawn(Network::Packet&);
			void HandlePlayerMoveAndLook(Network::Packet&);
			void HandlePlayerRemove(Network::Packet&);
			void HandleChatMessage(Network::Packet&);
			void HandleServiceResponse(Network::Packet&);
			void HandleMount(Network::Packet&);
			void HandleUnmount(Network::Packet&);

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);

		private:

			Network::TcpConnection::pointer mConnection;
			std::vector<boost::signals::connection> mEventLinks;

			static std::unordered_map<unsigned int, CallBack> mHandlers;
		};
	}
}