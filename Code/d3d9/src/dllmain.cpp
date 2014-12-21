// proxydll.cpp
#include <stdafx.h>
#include <DirectX/DirectXHook.h>


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

		if (strL.find("TESV.exe") != std::string::npos ||
			strL.find("Oblivion.exe") != std::string::npos)
		{
			g_instance = hModule;
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