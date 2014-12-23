#include <stdafx.h>
#include <dllmain.h>

#include <DirectX\DirectXHook.h>
#include <WinAPI.hpp>

int GameType = 0;

HMODULE g_hModule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			g_hModule = hModule;

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}

	return TRUE;
}
