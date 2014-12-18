// proxydll.cpp

#include "dllmain.h"
#include "scriptdragon.h"

typedef HANDLE(WINAPI *tCreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, PDWORD);
tCreateThread oCreateThread;

HINSTANCE gl_hThisInstance;

HANDLE WINAPI FakeCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, PDWORD lpThreadId)
{
	// ScriptDragonIsLoaded prevent the game from crashing!

	if (ScriptDragonIsLoaded == false && *(uint32_t*)lpParameter == 0x010CDD60)
	{
		ScriptDragonIsLoaded = true;
		DragonPluginInit(gl_hThisInstance);
		//MessageBox(NULL, "Script loaded", "mHook", MB_ICONWARNING);
	}

	return oCreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

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

			gl_hThisInstance = hModule;

			HINSTANCE kernel = GetModuleHandle("kernel32.dll");
			oCreateThread = (tCreateThread)GetProcAddress(kernel, "CreateThread");
			Mhook_SetHook((PVOID*)&oCreateThread, FakeCreateThread);
			
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			Mhook_Unhook((PVOID*)&FakeCreateThread); // Unhook fake thread which we created.

			break;
		}
	}
	return TRUE;
}