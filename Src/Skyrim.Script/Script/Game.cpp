#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;

::Game::Skyrim::Actor^ ::Game::Script::Skyrim::Game::PlaceAtMe(::Game::Skyrim::Actor^ self, UInt32 formId)
{
	return gcnew ::Game::Skyrim::Actor(::ObjectReference::PlaceAtMe((FreeScript::TESObjectREFR*)self->NativeHandle, ::Game::GetFormById(formId), 1, false, false));
}

::Game::Skyrim::Actor^ ::Game::Script::Skyrim::Game::GetPlayer()
{
	return gcnew ::Game::Skyrim::Actor(::Game::GetPlayer());
}

::Game::Skyrim::TESForm^ ::Game::Script::Skyrim::Game::GetFormById(System::UInt32 aiFormID)
{
	return gcnew ::Game::Skyrim::TESForm(::Game::GetFormById(aiFormID));
}

void ::Game::Script::Skyrim::Game::EnablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, System::UInt32 aiDisablePOVType)
{
	::Game::EnablePlayerControls(abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
}

void ::Game::Script::Skyrim::Game::SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage)
{
	::Game::SetInChargen(abDisableSaving, abDisableWaiting, abShowControlsDisabledMessage);
}

void ::Game::Script::Skyrim::Game::DisablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, System::UInt32 aiDisablePOVType)
{
	::Game::DisablePlayerControls(abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
}