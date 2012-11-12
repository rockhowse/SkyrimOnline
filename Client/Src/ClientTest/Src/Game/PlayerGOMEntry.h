#pragma once

#include <Game/ActorController.h>

namespace Skyrim
{
	namespace Game
	{
		class PlayerGOMEntry : public ::Game::GOMEntry<FreeScript::Character>
		{
		public:

			PlayerGOMEntry(FreeScript::Character* character);
			virtual ~PlayerGOMEntry();

			void Update();
			void Synchronize();
			
			std::string DoSerialize(bool pFull) const;
			void DoDeserialize(const std::string& plainData);

			void SetKey(uint32_t pKey);
			uint32_t GetKey() const;

		private:

			uint32_t mKey;
			
			::Game::GOMVariable<uint32_t> region;
			::Game::GOMVariable<bool> mount;
			::Game::GOMVariable<FreeScript::Character::Vector3> pos;
			::Game::GOMVariable<FreeScript::Character::Vector3> rot;
		};
	}
}