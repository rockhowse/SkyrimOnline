// proxydll.cpp
#include "plugin.h"
#include <string>

#pragma unmanaged

HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;

HMODULE g_hModule;

#pragma unmanaged

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

			g_hModule = hModule;

			LoadLibraryA("Skyrim.Script.dll");
			LoadLibraryA("Oblivion.Script.dll");

			break;
		}
	case DLL_PROCESS_DETACH:
		{		
			break;
		}
	}
	return TRUE;
}