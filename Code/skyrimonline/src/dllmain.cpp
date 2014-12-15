// proxydll.cpp

#include "dllmain.h"
#include "dragon.h"
#include "WinAPI.hpp"

typedef HANDLE(WINAPI *tCreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, PDWORD);
tCreateThread oCreateThread;

HINSTANCE gl_hOriginalDll;
HINSTANCE gl_hThisInstance;

void LoadOriginalDll();

void WINAPI D3DPERF_SetOptions( DWORD dwOptions )
{
	if (!gl_hOriginalDll) 
		LoadOriginalDll(); // looking for the "right d3d9.dll"

	// Hooking IDirect3D Object from Original Library
	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type) GetProcAddress(
		gl_hOriginalDll, "D3DPERF_SetOptions");

	// Debug
	if (!D3DPERF_SetOptions_fn)
	{
		MessageBoxA(0,"not found :(","0",0);
	}
	return (D3DPERF_SetOptions_fn (dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right d3d9.dll"

	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type) GetProcAddress( gl_hOriginalDll, "Direct3DCreate9");

    // Debug
	if (!D3DCreate9_fn)
    {
        OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
        ::ExitProcess(0); // exit the hard way
    }

	// Request pointer from Original Dll.
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	// Create my IDirect3D9 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	myIDirect3D9::instance = new myIDirect3D9(pIDirect3D9_orig);

	// Return pointer to hooking Object instead of "real one"
	return (myIDirect3D9::instance );
}

std::string GetPath()
{
	char buffer[MAX_PATH];

	// Getting path to system dir and to d3d8.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\d3d9.dll");
	
	return std::string(buffer);
}

void LoadOriginalDll(void)
{
	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(GetPath().c_str());

	// Debug
	if (!gl_hOriginalDll)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
}

void ExitInstance()
{
    OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	// Release the system's d3d9.dll
	if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
	    gl_hOriginalDll = NULL;
	}
}

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

			if(strL.find("TESV.exe") != std::string::npos)
			{
				gl_hThisInstance = hModule;

				HINSTANCE kernel = GetModuleHandle("kernel32.dll");
				oCreateThread = (tCreateThread)GetProcAddress(kernel, "CreateThread");
				Mhook_SetHook((PVOID*)&oCreateThread, FakeCreateThread);

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