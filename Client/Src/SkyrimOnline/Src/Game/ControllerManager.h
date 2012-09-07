#pragma once

#include "ActorController.h"

namespace Skyrim
{
	namespace Game
	{
		class ControllerManager
		{
		public:

			ControllerManager();
			~ControllerManager();
			void Add(ActorController* pPlayer);
			ActorController* Remove(ActorController* pPlayer);
			ActorController* Get(uint32_t);
			void Update(uint32_t);

		private:

			std::map<uint32_t, ActorController*> mCharacters;
		};
	}
}