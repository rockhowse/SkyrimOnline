// proxydll.cpp

#include "dllmain.h"

struct ParamInfo
{
	const char	* typeStr;
	unsigned int typeID;
	unsigned int isOptional;
};

typedef int(__thiscall* tUpdate)(void*);
tUpdate oUpdate;

int __fastcall Update(void* pthis, void* fastcall)
{
	return oUpdate(pthis);
}


#pragma unmanaged

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hModule);

			oUpdate = (tUpdate)Mhook_SetHook((PVOID*)0x40D800, Update);

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			Mhook_Unhook((PVOID*)&Update);

			break;
		}
	}
	return TRUE;
}