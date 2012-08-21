#include "stdafx.h"
#include "TimeManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		int TimeManager::DayPerMonth[12] =
		{
			31,28,31,30,31,30,31,31,30,31,30,31
		};
		//--------------------------------------------------------------------------------
		TimeManager::TimeManager()
			:mDay(0),mMonth(0),mHour(10),mTimeScale(24.f/6.f)
		{
			SetGlobalSetting(ID_TESGlobal::TimeScale, 20.f);
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetDay(float pDay)
		{
			mDay = pDay;
			SetGlobalSetting(ID_TESGlobal::GameDay,  mDay);
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetMonth(float pMonth)
		{
			mMonth = pMonth;
			SetGlobalSetting(ID_TESGlobal::GameMonth, mMonth);
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetHour(float pHour)
		{
			mHour = pHour;
			SetGlobalSetting(ID_TESGlobal::GameHour, mHour);
		}
		//--------------------------------------------------------------------------------
		void TimeManager::Update(uint32_t pElapsed)
		{
			mHour += (float(pElapsed)/3600000.f) * mTimeScale;
			if(mHour > 24.f)
			{
				mHour -= 24.f;
				mDay += 1;
				if(mDay > DayPerMonth[(int)mMonth])
				{
					mMonth++;
					mDay = 0;
				}
				if(mMonth > 12)
					mMonth = 0;
			}

			SetGlobalSetting(ID_TESGlobal::GameHour, mHour);
			SetGlobalSetting(ID_TESGlobal::GameDay,  mDay);
			SetGlobalSetting(ID_TESGlobal::GameMonth, mMonth);
		}
		//--------------------------------------------------------------------------------
	}
}