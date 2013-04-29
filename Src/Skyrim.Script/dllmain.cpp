#include "Stdafx.h"
#include "common/plugin.h"

#pragma unmanaged

extern "C" __declspec(dllexport) void main()
{
}

extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			std::string strL;
			strL.resize(MAX_PATH);
			GetModuleFileNameA(NULL, &strL[0], MAX_PATH) ;

			DisableThreadLibraryCalls((HMODULE)hModule);

			if(strL.find("TESV.exe") != std::string::npos)
			{
				SkyrimPluginInit(hModule);
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