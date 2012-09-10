#pragma once

#include <Logic/Session.h>
#include <Network/Server.h>
#include <Network/TcpConnection.h>
#include <System/DBWorkQueue.h>
#include <Game/TimeManager.h>
#include <Game/WeatherManager.h>
#include <Game/Map.h>

namespace Skyrim
{
	namespace Logic
	{
		class World
			: private boost::noncopyable
		{
		public:

			typedef boost::shared_ptr<World> pointer;
			/**
			 * Instantiate the server
			 * @param pPort The port to start the server on
			 */
			World(unsigned short pPort);

			/**
			 * Drops a player from the server, must never be called !
			 * @param pSession The session to drop from the server and world
			 */
			void Remove(Session::pointer pSession);

			Game::Map*	GetMap();

			void OnConnection(Framework::Network::TcpConnection::pointer pConnection);

			void OnUpdate(uint32_t pDelta);

			void Broadcast(Framework::Network::Packet& pPacket);

			void BroadcastPlayerMoveAndLook(Session::pointer pPlayer);

			uint32_t GetCount();

			void Run();

		private:

			Framework::Network::Server				mServer;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;

			std::unique_ptr<Framework::System::DBWorkQueue>	mDBWorkQueue;
			std::unique_ptr<Framework::System::WorkQueue>		mWorkQueue;

			uint32_t mId;

			Game::TimeManager		mTimeManager;
			Game::WeatherManager	mWeatherManager;
			Game::Map				mMap;
		};
	}
}