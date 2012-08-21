#pragma once

#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

#include <Logic/Session.h>

namespace Skyrim
{
	namespace Network
	{
		class Session;
	}
	namespace Game
	{
		/**
		 * Region class
		 */
		class Region
			: public boost::enable_shared_from_this<Region>
		{
		public:

			typedef boost::shared_ptr<Region> pointer;

			Region();
			virtual ~Region();

			void Update(uint32_t pDelta);

			void Add(Logic::Session::pointer pSession);
			void Remove(Logic::Session::pointer pSession);
			void BroadcastMoveAndLook( Logic::Session::pointer pSession );
		private:

			std::vector<Logic::Session::pointer> mPlayers;
			boost::mutex mLock;
		};
	}
}