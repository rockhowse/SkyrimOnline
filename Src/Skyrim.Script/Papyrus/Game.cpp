#include "Stdafx.h"
#pragma managed
#include "Game.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed
using namespace System;

SkyrimScript::Wrapper::Actor^ SkyrimScript::Papyrus::Game::GetPlayer()
{
	return gcnew SkyrimScript::Wrapper::Actor(::Game::GetPlayer());
}