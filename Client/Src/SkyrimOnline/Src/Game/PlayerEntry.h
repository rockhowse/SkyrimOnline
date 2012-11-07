#pragma once

namespace Skyrim
{
	namespace Game
	{
		class PlayerEntry : public ::Game::GOMEntry<FreeScript::Character>
		{
		public:

			PlayerEntry();

			void Update();
			void Synchronize();
			
			std::string DoSerialize(bool pFull) const;
			void DoDeserialize(const std::string& plainData);

			bool IsDead();
			FreeScript::Character& GetCharacter();

		private:

			FreeScript::Character mPlayer;
			
			::Game::GOMVariable<uint32_t> region;
			::Game::GOMVariable<bool> mount;
			::Game::GOMVariable<FreeScript::Character::Vector3> pos;
			::Game::GOMVariable<FreeScript::Character::Vector3> rot;
		};
	}
}