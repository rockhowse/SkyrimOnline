#include <DirectX\DirectXHook.h>

HINSTANCE gl_hOriginalDll;
HINSTANCE gl_hThisInstance;

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!gl_hOriginalDll)
		LoadOriginalDll();

	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3DPERF_SetOptions_fn = (D3D9_Type)GetProcAddress(gl_hOriginalDll, "D3DPERF_SetOptions");

	if (!D3DPERF_SetOptions_fn)
		MessageBoxA(0, "not found :(", "0", 0);

	MessageBox(NULL, "D3DPERF_SetOptions", "mHook", MB_ICONWARNING);

	return (D3DPERF_SetOptions_fn(dwOptions));
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll)
		LoadOriginalDll();

	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");

	if (!D3DCreate9_fn)
	{
		OutputDebugString("PROXYDLL: Pointer to original D3DCreate9 function not received ERROR ****\r\n");
		::ExitProcess(0);
	}

	IDirect3D9 *pIDirect3D9_orig = D3DCreate9_fn(SDKVersion);
	myIDirect3D9::instance = new myIDirect3D9(pIDirect3D9_orig);

	MessageBox(NULL, "Direct3DCreate9", "mHook", MB_ICONWARNING);

	return (myIDirect3D9::instance);
}

std::string GetPathToD3D9()
{
	char buffer[MAX_PATH];

	::GetSystemDirectory(buffer, MAX_PATH);

	strcat(buffer, "\\d3d9.dll");

	return std::string(buffer);
}

void LoadOriginalDll(void)
{
	if (!gl_hOriginalDll)
		gl_hOriginalDll = ::LoadLibrary(GetPathToD3D9().c_str());

	if (!gl_hOriginalDll)
	{
		OutputDebugString("PROXYDLL: Original d3d9.dll not loaded ERROR ****\r\n");
		::ExitProcess(0);
	}

	//MessageBox(NULL, "LoadOriginalDll", "mHook", MB_ICONWARNING);
}

void ExitInstance()
{
	OutputDebugString("PROXYDLL: ExitInstance called.\r\n");

	if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
		gl_hOriginalDll = NULL;
	}
}
