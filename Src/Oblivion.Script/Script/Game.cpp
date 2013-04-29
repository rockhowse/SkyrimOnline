#include "Stdafx.h"
#pragma managed
#include "Game.h"
#include "ObscriptCaller.hpp"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;

typedef bool (*_IsMenuMode)();
typedef void* (*_LookupFormByID)(UInt32);

const _LookupFormByID LookupFormByID = (_LookupFormByID)0x0046B250;
const _IsMenuMode IsMenuMode = (_IsMenuMode)0x00578F60;

Game::Oblivion::Actor^ Game::Script::Oblivion::Game::GetPlayer()
{
	return gcnew ::Game::Oblivion::Actor(*(void**)0x00B333C4);
}

Game::Oblivion::TESForm^ Game::Script::Oblivion::Game::GetFormById(UInt32 aiFormID)
{
	return gcnew ::Game::Oblivion::Actor(LookupFormByID(aiFormID));
}

void ::Game::Script::Oblivion::Game::EnablePlayerControls()
{
	ObscriptCaller caller("EnablePlayerControls");
	caller();
}

void ::Game::Script::Oblivion::Game::DisablePlayerControls()
{
	ObscriptCaller caller("DisablePlayerControls");
	caller();
}

void ::Game::Script::Oblivion::Game::EnableMouse()
{
	ObscriptCaller caller("EnableMouse");
	caller();
}

void ::Game::Script::Oblivion::Game::DisableMouse()
{
	ObscriptCaller caller("DisableMouse");
	caller();
}

bool ::Game::Script::Oblivion::Game::IsMenuMode()
{
	return ::IsMenuMode();
}


