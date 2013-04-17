// proxydll.h
#pragma once

// Exported function
IDirect3D9* WINAPI Direct3DCreate9 (UINT SDKVersion);

typedef void (__stdcall *TWait)(int);
extern TWait Wait;

// regular functions
void InitInstance(HANDLE hModule);
void ExitInstance(void);
void LoadOriginalDll(void);