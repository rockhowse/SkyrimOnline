#pragma once

#include <Game/Character.h>

namespace Skyrim
{
	namespace Game
	{
		class PlayerWatcher
		{
		public:

			PlayerWatcher();

			void Update(uint32_t);
			bool IsDead();
			Character& GetCharacter();

			boost::signal<void(Game::Character&)>			OnEnterWorld;
			boost::signal<void(Game::Character&, uint32_t)> OnMove;
			boost::signal<void(uint32_t)>					OnMount;
			boost::signal<void(uint32_t)>					OnRegion;
			boost::signal<void()>							OnUnmount;

		private:

			Character mPlayer;
			
			uint32_t mRegion;
			uint32_t mTimer;
			bool mMount;
			bool mEntered;
		};
	}
}