#include <winsock2.h>
#include <windows.h>
#include <malloc.h>
#include <string>
#include <sstream>
#include <iomanip>

#include "stdafx.h"
#include "detours.h"
#include "Version.hpp"

#pragma comment(lib, "detours.lib")


BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
		
		Version::Commit();

		LoadLibraryA("d3d9.dll");
		
        break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}