#include "Stdafx.h"

#pragma unmanaged

void OblivionPluginInit(HMODULE hModule)
{
	HMODULE hOblivion = GetModuleHandleA("Oblivion.Online.dll");
	CallOblivionFunction = (TCallOblivionFunction)GetProcAddress(hOblivion, "CallFunction");

	if(!CallOblivionFunction)
	{
		MessageBoxA(0,"Can't load the function !","Error",0);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			std::string strL;
			strL.resize(MAX_PATH);
			GetModuleFileNameA(NULL, &strL[0], MAX_PATH) ;

			DisableThreadLibraryCalls((HMODULE)hModule);

			if(strL.find("Oblivion.exe") != std::string::npos)
			{
				OblivionPluginInit(hModule);
			}
			break;
		}
	case DLL_PROCESS_DETACH:
		{		
			break;
		}
	}
	return TRUE;
}