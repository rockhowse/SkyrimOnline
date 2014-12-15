#include "FreeScript.h"
#include "skyscript.h"

namespace Skyrim
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
		*fSetting = ::GlobalVariable::GetValue((::TESGlobal*)pGlobalSetting); 
		return true;
	}

	bool SetGlobalSetting(int formIDSetting, float fSetting)
	{ 
		TESGlobal *pGlobalSetting = rtti_cast(::Game::GetFormById(formIDSetting), TESForm, TESGlobal); 
		if (!pGlobalSetting) 
			return false; 
		::GlobalVariable::SetValue((::TESGlobal*)pGlobalSetting, fSetting);
		return true;
	}
}