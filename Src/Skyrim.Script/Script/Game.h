#pragma once

#include <Wrapper/References.h>

namespace Game
{
	namespace Script
	{
		namespace Skyrim
		{
			public ref class Game
			{
			public:

				static ::Game::Skyrim::Actor^ PlaceAtMe(::Game::Skyrim::Actor^ self, UInt32 formId);
				static ::Game::Skyrim::Actor^ GetPlayer();
				static ::Game::Skyrim::TESForm^ GetFormById(System::UInt32 aiFormID);
				static void EnablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, System::UInt32 aiDisablePOVType);
				static void SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);
				static void DisablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, System::UInt32 aiDisablePOVType);
			};
		}
	}
}