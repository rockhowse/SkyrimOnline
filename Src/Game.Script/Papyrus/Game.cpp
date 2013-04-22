#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed

using namespace System;
using namespace Skyrim;

Script::Actor^ Script::Papyrus::Game::GetPlayer()
{
	return gcnew Skyrim::Script::Actor(::Game::GetPlayer());
}

Script::TESForm^ Script::Papyrus::Game::GetFormById(UInt32 aiFormID)
{
	return gcnew Script::TESForm(::Game::GetFormById(aiFormID));
}

void Script::Papyrus::Game::EnablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, UInt32 aiDisablePOVType)
{
	::Game::EnablePlayerControls(abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
}

void Script::Papyrus::Game::SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage)
{
	::Game::SetInChargen(abDisableSaving, abDisableWaiting, abShowControlsDisabledMessage);
}

void Script::Papyrus::Game::DisablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, UInt32 aiDisablePOVType)
{
	::Game::DisablePlayerControls(abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
}