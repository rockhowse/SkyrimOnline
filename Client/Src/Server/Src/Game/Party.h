#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace Skyrim
{
	namespace Network
	{
		class Session;
	}
	namespace Game
	{
		/**
		 * Party class
		 */
		class Party : public boost::enable_shared_from_this<Party>
		{
		public:

			typedef boost::shared_ptr<Party> pointer;

			Party();

			virtual ~Party();

		private:

			boost::shared_ptr<Network::Session> mLeader;
			std::vector<boost::shared_ptr<Network::Session>> mMembers;
		};
	}
}