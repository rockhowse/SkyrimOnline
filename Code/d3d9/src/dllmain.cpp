// proxydll.cpp
#include <stdafx.h>
#include <DirectX/DirectXHook.h>

#pragma unmanaged

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		std::string strL;

		strL.resize(MAX_PATH);
		GetModuleFileName(NULL, &strL[0], MAX_PATH);

		DisableThreadLibraryCalls(hModule);

		if (strL.find("TESV.exe") != std::string::npos)
		{
			gl_hThisInstance = hModule;
			LoadOriginalDll();
		}

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		ExitInstance();

		break;
	}
	}
	return TRUE;
}