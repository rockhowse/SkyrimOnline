#include "Stdafx.h"
#pragma managed
#include "Globals.h"
#include "ObscriptCaller.hpp"
#pragma managed

using namespace System;
using namespace Game;
using namespace Game::Script;

#pragma unmanaged

class TESGlobal
{
public:

	char pad00to24[0x24 - 0x00];
	float data;
};

class TimeGlobals
{
public:
	static TimeGlobals* Singleton()
	{
		return (TimeGlobals*)0x00B332E0;
	}

	TimeGlobals()
	{

	}

	~TimeGlobals()
	{

	}

	static float& GameYear() 
	{
		return Singleton()->gameYear->data;
	}

	static float& GameMonth() 
	{
		return Singleton()->gameMonth->data;
	}

	static float& GameDay() 
	{
		return Singleton()->gameDay->data;
	}

	static float& GameHour() 
	{
		return Singleton()->gameHour->data;
	}

	static float& GameDaysPassed() 
	{
		return Singleton()->gameDaysPassed->data;
	}

	static float& TimeScale() 
	{
		return Singleton()->timeScale->data;
	}
private:
	TESGlobal	* gameYear;
	TESGlobal	* gameMonth;
	TESGlobal	* gameDay;
	TESGlobal	* gameHour;
	TESGlobal	* gameDaysPassed;
	TESGlobal	* timeScale;
};
#pragma managed

void ::Game::Script::Oblivion::Globals::SetScale(float pValue)
{
	TimeGlobals::TimeScale() = pValue;
}

void ::Game::Script::Oblivion::Globals::SetHour(float pValue)
{
	TimeGlobals::GameHour() = pValue;
}

void ::Game::Script::Oblivion::Globals::SetDay(float pValue)
{
	TimeGlobals::GameDay() = pValue;
}

void ::Game::Script::Oblivion::Globals::SetMonth(float pValue)
{
	TimeGlobals::GameMonth() = pValue;
}

void ::Game::Script::Oblivion::Globals::SetYear(float pValue)
{
	TimeGlobals::GameYear() = pValue;
}