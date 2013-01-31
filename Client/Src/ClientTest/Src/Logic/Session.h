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
			boost::signal<void()>					OnSpawn;

			std::string GetName();

		protected:

			void OnSynchronize();

			void HandleChatMessage(Network::Packet&);
			void HandleServiceResponse(Network::Packet&);
			void HandleInitialData(Network::Packet&);

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);

		private:

			std::string mName;
			Network::TcpConnection::pointer mConnection;
			std::vector<boost::signals::connection> mEventLinks;
		};
	}
}