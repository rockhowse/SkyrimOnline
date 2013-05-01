#pragma once

#include "../Wrapper/GameObjects.h"

namespace Game
{
	namespace Script
	{
		namespace Oblivion
		{
			public ref class Game
			{
			public:

				static ::Game::Oblivion::Actor^ PlaceAtMe(::Game::Oblivion::Actor^ self, UInt32 id);
				static ::Game::Oblivion::Actor^ GetPlayer();
				static ::Game::Oblivion::TESForm^ GetFormById(UInt32 aiFormID);
				static bool IsMenuMode();
				static void EnablePlayerControls();
				static void DisablePlayerControls();
				static void EnableMouse();
				static void DisableMouse();
			};
		}
	}
}