#pragma once

#include <stdafx.h>

// Exported function
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);

extern myIDirect3DDevice9* gl_pmyIDirect3DDevice9;
extern myIDirect3D9* gl_pmyIDirect3D9;

// regular functions
void InitInstance(HANDLE hModule);
void ExitInstance(void);
void LoadOriginalDll(void);