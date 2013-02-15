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
			engine->RegisterReferenceClass(TimeManager);
			engine->RegisterGlobal("TimeManager Time", this);
			engine->RegisterMethod(TimeManager, "void SetTimeSpeed(float)",SetTimeSpeed);


			engine->RegisterPODType(Date);
			engine->RegisterProperty(Date, "float Hour", Hour);
			engine->RegisterProperty(Date, "float Day", Day);
			engine->RegisterProperty(Date, "float Month", Month);
			engine->RegisterProperty(Date, "float Year", Year);

			engine->RegisterMethod(TimeManager, "void SetDate(Date &in)", SetDate);
			engine->RegisterMethod(TimeManager, "Date GetDate()", GetDate);
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