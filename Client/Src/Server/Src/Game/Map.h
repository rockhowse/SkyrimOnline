#pragma once

#include <stdint.h>
#include <Game/Region.h>
#include <Logic/Session.h>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <map>

namespace Skyrim
{
	namespace Game
	{
		/**
		 * Map class
		 */
		class Map 
			: public boost::enable_shared_from_this<Map>
		{
		public:

			typedef boost::shared_ptr<Map> pointer;

			Map();
			virtual ~Map();

			void Update(uint32_t pDelta);

			bool EnterRegion(const uint32_t pRegion, Logic::Session::pointer);
			bool LeaveRegion(const uint32_t pRegion, Logic::Session::pointer);

			Region::pointer GetRegion(uint32_t pRegion);

			bool IsValid(uint32_t pRegion);

		private:

			std::map<uint32_t, Region::pointer> mRegions;
		};
	}
}