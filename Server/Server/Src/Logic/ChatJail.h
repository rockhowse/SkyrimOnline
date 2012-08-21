#pragma once

#include <boost/timer.hpp>
#include <stdint.h>

namespace Skyrim
{
	namespace Logic
	{

		/**
		 * @class ChatJail
		 */
		class ChatJail
		{
		public:

			ChatJail();
			~ChatJail();

			void Update(uint32_t pDelta);

			bool CanSend();

		protected:

			uint32_t mBurst;
			uint32_t mLastMessage;
			int32_t  mJailTime;
			uint32_t mAccumulator;
		};
	}
}