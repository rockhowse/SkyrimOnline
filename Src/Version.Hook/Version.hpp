#pragma once

#include <windows.h>

struct Version
{
	static void Commit();

	static HMODULE module;
	static PBYTE r_VerQueryValueA;
	static PBYTE r_VerQueryValueW;
	static PBYTE r_GetFileVersionInfoSizeW;
	static PBYTE r_GetFileVersionInfoSizeA;
	static PBYTE r_GetFileVersionInfoA;
	static PBYTE r_GetFileVersionInfoW;
	static PBYTE r_GetFileVersionInfoSizeExA;
	static PBYTE r_GetFileVersionInfoSizeExW;
	static PBYTE r_GetFileVersionInfoExA;
	static PBYTE r_GetFileVersionInfoExW;
};