#include "Stdafx.h"
#pragma managed
#include "Globals.h"
#include "FreeScript/Data.hpp"
#include "common/enums.h"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;


void ::Game::Script::Skyrim::Globals::SetScale(float pValue)
{
	::FreeScript::SetGlobalSetting(ID_TESGlobal::TimeScale, pValue);
}

void ::Game::Script::Skyrim::Globals::SetHour(float pValue)
{
	::FreeScript::SetGlobalSetting(ID_TESGlobal::GameHour, pValue);
}

void ::Game::Script::Skyrim::Globals::SetDay(float pValue)
{
	::FreeScript::SetGlobalSetting(ID_TESGlobal::GameDay, pValue);
}

void ::Game::Script::Skyrim::Globals::SetMonth(float pValue)
{
	::FreeScript::SetGlobalSetting(ID_TESGlobal::GameMonth, pValue);
}

void ::Game::Script::Skyrim::Globals::SetYear(float pValue)
{
	::FreeScript::SetGlobalSetting(ID_TESGlobal::GameYear, pValue);
}