#include <Game/Region.h>

namespace Skyrim
{
	namespace Game
	{
		//---------------------------------------------------------------------
		Region::Region()
		{

		}
		//---------------------------------------------------------------------
		Region::~Region()
		{

		}
		//---------------------------------------------------------------------
		void Region::Update(uint32_t pDelta)
		{
			mLock.lock();
			auto copy = mPlayers;
			mLock.unlock();

			std::for_each(copy.begin() , copy.end(), [pDelta](Logic::Session::pointer pPlayer)
			{
				pPlayer->Update(pDelta);
			});
		}
		//---------------------------------------------------------------------
		void Region::Add(Logic::Session::pointer pSession)
		{
			boost::mutex::scoped_lock lock(mLock);
			if(std::find(mPlayers.begin(), mPlayers.end(), pSession) == mPlayers.end())
			{
				std::for_each(mPlayers.begin() , mPlayers.end(), [pSession](Logic::Session::pointer pPlayer)
				{
					pPlayer->SendSpawnPlayer(pSession);
					pSession->SendSpawnPlayer(pPlayer);
				});

				mPlayers.push_back(pSession);
			}
		}
		//---------------------------------------------------------------------
		void Region::Remove(Logic::Session::pointer pSession)
		{
			boost::mutex::scoped_lock lock(mLock);

			auto itor = std::find(mPlayers.begin(), mPlayers.end(), pSession);
			if(itor != mPlayers.end())
			{
				mPlayers.erase(itor);
				std::for_each(mPlayers.begin() , mPlayers.end(), [&pSession](Logic::Session::pointer pPlayer)
				{
					pPlayer->SendRemove(pSession);
					pSession->SendRemove(pPlayer);
				});
			}
		}
		//---------------------------------------------------------------------
		void Region::BroadcastMoveAndLook( Logic::Session::pointer pSession )
		{
			auto itor = std::find(mPlayers.begin(), mPlayers.end(), pSession);
			if(itor != mPlayers.end())
			{
				std::for_each(mPlayers.begin() , mPlayers.end(), [&pSession](Logic::Session::pointer pPlayer)
				{
					if(pSession.get() != pPlayer.get())
						pPlayer->SendMoveAndLook(pSession);
				});
			}
		}
		//---------------------------------------------------------------------
	}
}