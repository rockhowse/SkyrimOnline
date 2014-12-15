// proxydll.cpp
#include <stdafx.h>

HINSTANCE gl_hGameHook;
HINSTANCE gl_hThisInstance;

void LoadOriginalDll(void)
{
	// try to load the SkyrimOnline Plugin, if pointer empty
	if (!gl_hGameHook)
		gl_hGameHook = ::LoadLibrary("SkyrimOnline.dll");

	// Debug
	if (!gl_hGameHook)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!gl_hGameHook) 
		LoadOriginalDll(); // looking for the "SkyrimOnline Plugin"

	// Hooking IDirect3D Object from Original Library
	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type)GetProcAddress(gl_hGameHook, "D3DPERF_SetOptions");

	// Debug
	if (!D3DPERF_SetOptions_fn)
		MessageBoxA(0, "not found :(", "0", 0);
	
	return (D3DPERF_SetOptions_fn(dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hGameHook) 
		LoadOriginalDll(); // looking for the "SkyrimOnline Plugin"

	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(gl_hGameHook, "Direct3DCreate9");

	// Debug
	if (!D3DCreate9_fn)
	{
		OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}

	// Request pointer from Original Dll.
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	// Return pointer to hooking Object instead of "real one"
	return pIDirect3D9_orig;
}

void ExitInstance()
{
	OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	// Release the SkyrimOnline Plugin
	if (gl_hGameHook)
	{
		::FreeLibrary(gl_hGameHook);
		gl_hGameHook = NULL;
	}
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