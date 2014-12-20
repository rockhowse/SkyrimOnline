#include <stdafx.h>
#include <dllmain.h>

#include <DirectX\DirectXHook.h>
#include <WinAPI.hpp>

// ILOVEPIE did GetSkyrimSearchString & GetOblivionSearchString.

void GetSkyrimSearchString(std::string &search_string)
{
	char output[256];

	GetPrivateProfileString("Loader", "RuntimeName", "TESV.exe", &output[0], 256, ".\\Data\\SKSE\\skse.ini");

	search_string = std::string(&output[0]);
}
void GetOblivionSearchString(std::string &search_string)
{
	char output[256];

	GetPrivateProfileString("Loader", "RuntimeName", "Oblivion.exe", &output[0], 256, ".\\Data\\OBSE\\obse.ini");

	search_string = std::string(&output[0]);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			std::string ModuleFileName, findSkyrimString, findOblivionString;

			ModuleFileName.resize(MAX_PATH);
			GetModuleFileName(NULL, &ModuleFileName[0], MAX_PATH);

			DisableThreadLibraryCalls(hModule);

			GetSkyrimSearchString(findSkyrimString); // use SKSE.ini to detect the correct name for Skyrim.
			GetOblivionSearchString(findOblivionString); // use OBSE.ini to detect the correct name for Oblivion.

			if (ModuleFileName.find(findSkyrimString) != std::string::npos || ModuleFileName.find(findOblivionString) != std::string::npos)
			{
				InitInstance(hModule);

				if (ModuleFileName.find(findSkyrimString) != std::string::npos)
				{
					GameType = 1; // Set the game to Skyrim.
					LoadLibraryA("SkyrimOnline.dll");
				}
				else
				{
					GameType = 2; // Set the game to Oblivion.
					LoadLibraryA("OblivionOnline.dll");
				}

				HookDInput();
				HookWinAPI();
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
