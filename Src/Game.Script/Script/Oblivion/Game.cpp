#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;

typedef bool (*_IsMenuMode)();

bool::Game::Script::Oblivion::Game::IsMenuMode()
{
	return ((_IsMenuMode)0x00578F60)();
}
