#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;

typedef bool (*_IsMenuMode)();

Game::Oblivion::Actor^ Game::Script::Oblivion::Game::GetPlayer()
{
	return gcnew ::Game::Oblivion::Actor(*(void**)0x00B333C4);
}

bool ::Game::Script::Oblivion::Game::IsMenuMode()
{
	return ((_IsMenuMode)0x00578F60)();
}
