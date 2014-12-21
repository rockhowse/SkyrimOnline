#include <stdafx.h>

HINSTANCE g_gameHook;

void LoadOriginalDll(void)
{
	// Try to load the SkyrimOnline Plugin, if pointer empty
	if (!g_gameHook)
		g_gameHook = ::LoadLibrary("Logic.dll");

	// Debug
	if (!g_gameHook)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!g_gameHook)
		LoadOriginalDll(); // Looking for the "SkyrimOnline Plugin"

	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type)GetProcAddress(g_gameHook, "D3DPERF_SetOptions");

	// Debug
	if (!D3DPERF_SetOptions_fn)
		MessageBoxA(0, "not found :(", "0", 0);

	return (D3DPERF_SetOptions_fn(dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!g_gameHook)
		LoadOriginalDll(); // Looking for the "SkyrimOnline Plugin"

	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(g_gameHook, "Direct3DCreate9");

	// Debug
	if (!D3DCreate9_fn)
	{
		OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}

	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);

	return pIDirect3D9_orig;
}

void ExitInstance(void)
{
	OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	// Release the SkyrimOnline Plugin
	if (g_gameHook)
	{
		::FreeLibrary(g_gameHook);
		g_gameHook = NULL;
	}
}
