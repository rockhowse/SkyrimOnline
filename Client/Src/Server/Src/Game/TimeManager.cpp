#include "stdafx.h"
#include "TimeManager.hpp"
#include "ScriptEngine.hpp"
#include "GameWorld.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void TimeManager::Register(ScriptEngine* engine)
		{
			engine->RegisterReferenceClass("TimeManager");
			engine->RegisterGlobal("TimeManager Time", this);
			engine->RegisterMethod("TimeManager", "void SetTimeSpeed(float)",asMETHOD(TimeManager,SetTimeSpeed));


			engine->RegisterPODType(Date, sizeof(Date));
			engine->RegisterProperty("Date", "float Hour", asOFFSET(Date, Hour));
			engine->RegisterProperty("Date", "float Day", asOFFSET(Date, Day));
			engine->RegisterProperty("Date", "float Month", asOFFSET(Date, Month));
			engine->RegisterProperty("Date", "float Year", asOFFSET(Date, Year));

			engine->RegisterMethod("TimeManager", "void SetDate(Date &in)", asMETHOD(TimeManager, SetDate));
			engine->RegisterMethod("TimeManager", "Date GetDate()", asMETHOD(TimeManager, GetDate));
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetTimeSpeed(float speed)
		{

		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetDate(Date& date)
		{
			WorldState state;
			state.SetDate({{date.Hour, date.Day, date.Month, date.Year}});
			TheGameWorld->GetWorldManager().SendWorldStateUpdate(state);
		}
		//--------------------------------------------------------------------------------
		TimeManager::Date TimeManager::GetDate()
		{
			return Date();
		}
		//--------------------------------------------------------------------------------
	}
}