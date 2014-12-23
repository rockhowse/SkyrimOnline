#pragma once

#include <stdafx.h>

// Exported function
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion);

extern myIDirect3DDevice9* g_pIDirect3DDevice9;
extern myIDirect3D9* g_pIDirect3D9;

// regular functions
void HookDirect3D9();