#include "TimeManager.h"
#include <enums.h>
#include <skyscript.h>
#include "Data.h"

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	int TimeManager::DayPerMonth[12] =
	{
		31,28,31,30,31,30,31,31,30,31,30,31
	};
	//--------------------------------------------------------------------------------
	TimeManager::TimeManager()
	{
	}
	//--------------------------------------------------------------------------------
	void TimeManager::SetDate(const TimeManager::Date& pDate)
	{
		SetGlobalSetting(ID_TESGlobal::GameHour,  pDate.Hour );
		SetGlobalSetting(ID_TESGlobal::GameDay,   pDate.Day  );
		SetGlobalSetting(ID_TESGlobal::GameMonth, pDate.Month);
		//SetGlobalSetting(ID_TESGlobal::GameYear,  pDate.Year );
	}
	//--------------------------------------------------------------------------------
	TimeManager::Date TimeManager::GetDate()
	{
		Date date;
		GetGlobalSetting(ID_TESGlobal::GameHour, &date.Hour );
		GetGlobalSetting(ID_TESGlobal::GameDay,  &date.Day  );
		GetGlobalSetting(ID_TESGlobal::GameMonth,&date.Month);
		GetGlobalSetting(ID_TESGlobal::GameYear, &date.Year );

		return date;
	}
	//--------------------------------------------------------------------------------
}