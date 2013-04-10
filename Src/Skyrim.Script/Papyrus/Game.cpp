#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed
using namespace System;

Skyrim::Script::Wrapper::Actor^ Skyrim::Script::Papyrus::Game::GetPlayer()
{
	return gcnew Skyrim::Script::Wrapper::Actor(::Game::GetPlayer());
}