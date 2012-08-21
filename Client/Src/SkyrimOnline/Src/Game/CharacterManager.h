#pragma once

#include "RemotePlayer.h"

namespace Skyrim
{
	namespace Game
	{
		class CharacterManager
		{
		public:

			CharacterManager();
			~CharacterManager();
			void Add(RemotePlayer* pPlayer);
			RemotePlayer* Remove(RemotePlayer* pPlayer);
			RemotePlayer* Get(uint32_t);
			void Update(uint32_t);

		private:

			std::map<uint32_t, RemotePlayer*> mCharacters;
		};
	}
}