#pragma once

#include <Wrapper/Oblivion/GameObjects.h>

namespace Game
{
	namespace Script
	{
		namespace Oblivion
		{
			public ref class Game
			{
			public:

				static ::Game::Oblivion::Actor^ GetPlayer();
				static ::Game::Oblivion::TESForm^ GetFormById(UInt32 aiFormID);
				static bool IsMenuMode();
			};
		}
	}
}