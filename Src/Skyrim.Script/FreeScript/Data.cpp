#include "stdafx.h"
#include "Data.hpp"
#include <common/skyscript.h>

namespace FreeScript
{
	TESDataHandler* TESDataHandler::GetInstance()
	{
		return *((TESDataHandler**)0x12e2cb8);
	}

	bool GetGlobalSetting(int formIDSetting, float *fSetting)
	{ 
		TESGlobal *pGlobalSetting = rtti_cast(::Game::GetFormById(formIDSetting), TESForm, TESGlobal); 
		if (!pGlobalSetting) 
			return false; 
		*fSetting = ::GlobalVariable::GetValue(pGlobalSetting); 
		return true;
	}

	bool SetGlobalSetting(int formIDSetting, float fSetting)
	{ 
		TESGlobal *pGlobalSetting = rtti_cast(::Game::GetFormById(formIDSetting), TESForm, TESGlobal); 
		if (!pGlobalSetting) 
			return false; 
		::GlobalVariable::SetValue(pGlobalSetting, fSetting); 
		return true;
	}
}