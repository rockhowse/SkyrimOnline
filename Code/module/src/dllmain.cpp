#include <stdafx.h>
#include <DirectX\DirectXHook.h>
#include <VersionHook.h>
#include <WinAPI.hpp>

extern HINSTANCE gl_hThisInstance;

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

			LoadBaseVersion(); // Get the Version function or the game won't start.

			if (strL.find("TESV.exe") != std::string::npos)
			{
				gl_hThisInstance = hModule;
				LoadOriginalDll();

				LoadLibrary("SkyrimOnline.dll");

				HookDInput();
				HookWinAPI();

				//MessageBox(NULL, strL.c_str(), "mHook", MB_ICONWARNING);
			}

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			ReleaseWinAPI();
			ReleaseDInput();
			ExitInstance();

			break;
		}
	}
	return TRUE;
}