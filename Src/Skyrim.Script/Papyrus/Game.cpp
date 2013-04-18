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

Script::TESForm^ Script::Papyrus::Game::Forms::get(UInt32 aiFormID)
{
	return gcnew Script::TESForm(::Game::GetFormById(aiFormID));
}