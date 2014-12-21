#include <DirectX\DirectXHook.h>

// global variables
#pragma data_seg (".d3d9_shared")
myIDirect3DDevice9* g_pIDirect3DDevice9;
myIDirect3D9* g_pIDirect3D9;
HINSTANCE g_realD3d9;
HINSTANCE g_instance;
#pragma data_seg ()

void LoadOriginalDll(void)
{
	char buffer[MAX_PATH];

	::GetSystemDirectory(buffer, MAX_PATH);

	strcat(buffer, "\\d3d9.dll");

	if (!g_realD3d9) 
		g_realD3d9 = ::LoadLibrary(buffer);

	if (!g_realD3d9)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!g_realD3d9)
		LoadOriginalDll(); // looking for the "right d3d9.dll"

	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type)GetProcAddress(g_realD3d9, "D3DPERF_SetOptions");

	// Debug
	if (!D3DPERF_SetOptions_fn)
		MessageBoxA(0, "not found :(", "0", 0);

	return (D3DPERF_SetOptions_fn(dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!g_realD3d9)
		LoadOriginalDll();

	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(g_realD3d9, "Direct3DCreate9");

	// Debug
	if (!D3DCreate9_fn)
	{
		OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
		::ExitProcess(0); // exit the hard way
	}
 
	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);
	g_pIDirect3D9 = new myIDirect3D9(pIDirect3D9_orig);

	return (g_pIDirect3D9);
}

void InitInstance(HANDLE hModule)
{
	OutputDebugString("PROXYDLL: InitInstance called.\r\n");

	// Initialisation
	g_realD3d9 = NULL;
	g_instance = NULL;
	g_pIDirect3D9 = NULL;
	g_pIDirect3DDevice9 = NULL;

	// Storing Instance handle into global var
	g_instance = (HINSTANCE)hModule;
}

void ExitInstance()
{
	OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	// Release the system's d3d9.dll
	if (g_realD3d9)
	{
		::FreeLibrary(g_realD3d9);
		g_realD3d9 = NULL;
	}
}

