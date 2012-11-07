#pragma once

#include <Game/PlayerGOMEntry.h>

namespace Skyrim
{
	namespace Game
	{
		class PlayerGOMServer : public ::Game::GOMServer<PlayerGOMEntry, 'plyr'>
		{
		public:

			PlayerGOMServer();

		protected:

			void DoAdd(WrappedType*, int32, int32 = -1);
			void DoRemove(int32, int32);
			void DoUpdate();

			void UpdateEntry(int32_t id, int32_t state, const std::string& serializedData);

		private:

			friend class PlayerGOMEntry;
			std::map<uint32_t, boost::shared_ptr<ActorController> > mControllers;
		};
	}
}