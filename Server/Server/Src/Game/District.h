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
		 * >District class
		 */
		class District
		{
		public:

			/**
			 * Constructs a District.
			 */
			District();

			/**
			 * Destroys a District.
			 */
			virtual ~District();

		private:
		};
	}
}