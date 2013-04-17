#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed
using namespace System;

Skyrim::Script::Actor^ Skyrim::Script::Papyrus::Game::GetPlayer()
{
	return gcnew Skyrim::Script::Actor(::Game::GetPlayer());
}