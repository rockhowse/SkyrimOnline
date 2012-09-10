#include <Logic/World.h>
#include <System/Log.h>

using boost::asio::ip::tcp;
using namespace Framework;

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		World::World(unsigned short pPort)
			:mId(0), mServer(pPort)
		{
			System::Log::Create("SkyrimOnlineServer.log");
			System::Log::Print("               Skyrim Online        ");
			System::Log::Print("Memory model : " + std::to_string((unsigned long long)sizeof(void*) * 8) + " bits				   ");

			Session::Setup();

			mWorkQueue.reset(new System::WorkQueue(1));

			mServer.OnConnection.connect(boost::bind(&World::OnConnection, this, _1));
			mServer.OnUpdate.connect(boost::bind(&World::OnUpdate, this, _1));

			mServer.RunOnce();
		}
		//---------------------------------------------------------------------
		Game::Map* World::GetMap()
		{
			return &mMap;
		}
		//---------------------------------------------------------------------
		void World::OnConnection(Framework::Network::TcpConnection::pointer pConnection)
		{
			Session::pointer session = boost::make_shared<Session>(pConnection, this, ++mId);

			mGuard.lock();
			mSessions.push_back(session);
			mGuard.unlock();

			session->Start();
		}
		//---------------------------------------------------------------------
		void World::OnUpdate(uint32_t pDelta)
		{
			mGuard.lock();
			auto sessionCopy(mSessions);
			mGuard.unlock();

			// Work with authenticating sessions
			std::for_each(sessionCopy.begin(), sessionCopy.end(),
				[this, pDelta](Session::pointer pSession)
			{
				// Update must be synchronous
				pSession->Update(pDelta);
			});

			mMap.Update(pDelta);
		}
		//---------------------------------------------------------------------
		void World::Remove(Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
			{
				mSessions.erase(itor);
			}
		}
		//---------------------------------------------------------------------
		uint32_t World::GetCount()
		{
			return mSessions.size();
		}
		//---------------------------------------------------------------------
		void World::Broadcast(Framework::Network::Packet& pPacket)
		{
			std::for_each(mSessions.begin(), mSessions.end(),
				[&pPacket](Session::pointer pSession)
			{
				pSession->Write(pPacket);
			});
		}
		//---------------------------------------------------------------------
		void World::BroadcastPlayerMoveAndLook(Session::pointer pPlayer)
		{
			std::for_each(mSessions.begin(), mSessions.end(),
				[&pPlayer](Session::pointer pSession)
			{
				if(pSession != pPlayer)
					pSession->HandlePlayerEvent(pPlayer);
			});
		}
		//---------------------------------------------------------------------
		void World::Run()
		{
			mServer.RunOnce();
		}
		//---------------------------------------------------------------------
	}
}