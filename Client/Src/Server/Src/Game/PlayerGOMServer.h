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

			void _Add(boost::shared_ptr<ActorController> ctrlr, int32_t replicationState, int32_t id = -1);

		protected:

			void DoAdd(WrappedType*, int32_t, int32_t = -1);
			void DoRemove(int32_t, int32_t) override;
			void DoUpdate();

			void UpdateEntry(int32_t id, int32_t state, const std::string& serializedData);

		private:

			friend class PlayerGOMEntry;
			std::map<uint32_t, boost::shared_ptr<ActorController> > mControllers;
		};
	}
}