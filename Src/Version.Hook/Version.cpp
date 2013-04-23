#include "stdafx.h"
#include "Version.hpp"

HMODULE Version::module;
PBYTE Version::r_VerQueryValueA;
PBYTE Version::r_VerQueryValueW;
PBYTE Version::r_GetFileVersionInfoSizeW;
PBYTE Version::r_GetFileVersionInfoSizeA;
PBYTE Version::r_GetFileVersionInfoA;
PBYTE Version::r_GetFileVersionInfoW;
PBYTE Version::r_GetFileVersionInfoSizeExA;
PBYTE Version::r_GetFileVersionInfoSizeExW;
PBYTE Version::r_GetFileVersionInfoExA;
PBYTE Version::r_GetFileVersionInfoExW;

std::string GetPath()
{
	char buffer[MAX_PATH];
	// Getting path to system dir and to d3d8.dll
	::GetSystemDirectory(buffer,MAX_PATH);
	// Append dll name
	strcat(buffer,"\\version.dll");

	return std::string(buffer);
}

void LoadOriginalDll(void)
{
	// try to load the system's d3d9.dll, if pointer empty
	if (!Version::module) 
		Version::module = ::LoadLibrary(GetPath().c_str());

	// Debug
	if (!Version::module)
	{
		::ExitProcess(0); // exit the hard way
	}

}

void Version::Commit()
{
	LoadOriginalDll();

	r_VerQueryValueA = (PBYTE)GetProcAddress(module, "VerQueryValueA");
	r_VerQueryValueW = (PBYTE)GetProcAddress(module, "VerQueryValueW");
	r_GetFileVersionInfoA = (PBYTE)GetProcAddress(module, "GetFileVersionInfoA");
	r_GetFileVersionInfoW = (PBYTE)GetProcAddress(module, "GetFileVersionInfoW");
	r_GetFileVersionInfoSizeA = (PBYTE)GetProcAddress(module, "GetFileVersionInfoSizeA");
	r_GetFileVersionInfoSizeW = (PBYTE)GetProcAddress(module, "GetFileVersionInfoSizeW");
	r_GetFileVersionInfoSizeExA = (PBYTE)GetProcAddress(module, "GetFileVersionInfoSizeExA");
	r_GetFileVersionInfoSizeExW = (PBYTE)GetProcAddress(module, "GetFileVersionInfoSizeExW");
	r_GetFileVersionInfoExA = (PBYTE)GetProcAddress(module, "GetFileVersionInfoExA");
	r_GetFileVersionInfoExW = (PBYTE)GetProcAddress(module, "GetFileVersionInfoExW");
}


typedef BOOL(WINAPI *t_VerQueryValueA)(_In_   LPCVOID pBlock,_In_   LPCTSTR lpSubBlock,_Out_  LPVOID *lplpBuffer,_Out_  PUINT puLen);
typedef BOOL(WINAPI *t_GetFileVersionInfoA)(_In_ LPCTSTR lptstrFilename,_Reserved_  DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData);
typedef DWORD(WINAPI *t_GetFileVersionInfoSizeA)( _In_ LPCTSTR lpSubBlock, _Out_opt_  LPDWORD lpdwHandle);
typedef DWORD(WINAPI* t_GetFileVersionInfoSizeExA)(_In_ DWORD dwFlags,_In_ LPCTSTR lptstrFilename,_Out_ LPDWORD lpdwHandle);
typedef BOOL(WINAPI* t_GetFileVersionInfoExA)(_In_ DWORD dwFlags,_In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData);

typedef BOOL(WINAPI *t_VerQueryValueW)(_In_   LPCVOID pBlock,_In_   LPCWSTR lpSubBlock,_Out_  LPVOID *lplpBuffer,_Out_  PUINT puLen);
typedef BOOL(WINAPI *t_GetFileVersionInfoW)(_In_ LPCWSTR lptstrFilename,_Reserved_  DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData);
typedef DWORD(WINAPI *t_GetFileVersionInfoSizeW)( _In_ LPCWSTR lpSubBlock, _Out_opt_  LPDWORD lpdwHandle);
typedef DWORD(WINAPI* t_GetFileVersionInfoSizeExW)(_In_ DWORD dwFlags,_In_ LPCWSTR lptstrFilename,_Out_ LPDWORD lpdwHandle);
typedef BOOL(WINAPI* t_GetFileVersionInfoExW)(_In_ DWORD dwFlags,_In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData);


BOOL WINAPI VerQueryValueA(_In_   LPCVOID pBlock,_In_   LPCTSTR lpSubBlock,_Out_  LPVOID *lplpBuffer,_Out_  PUINT puLen)
{
	BOOL ret = ((t_VerQueryValueA)Version::r_VerQueryValueA)(pBlock, lpSubBlock, lplpBuffer, puLen);
	return ret;
}

BOOL WINAPI GetFileVersionInfoA(_In_ LPCTSTR lptstrFilename,_Reserved_  DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData)
{
	BOOL ret = ((t_GetFileVersionInfoA)Version::r_GetFileVersionInfoA)(lptstrFilename, dwHandle, dwLen, lpData);
	return ret;
}

DWORD WINAPI GetFileVersionInfoSizeA( _In_ LPCTSTR lpSubBlock, _Out_opt_  LPDWORD lpdwHandle)
{
	DWORD ret = ((t_GetFileVersionInfoSizeA)Version::r_GetFileVersionInfoSizeA)(lpSubBlock, lpdwHandle);
	return ret;
}

DWORD WINAPI GetFileVersionInfoSizeExA(_In_ DWORD dwFlags,_In_ LPCTSTR lptstrFilename,_Out_ LPDWORD lpdwHandle)
{
	DWORD ret = ((t_GetFileVersionInfoSizeExA)Version::r_GetFileVersionInfoSizeExA)(dwFlags, lptstrFilename, lpdwHandle);
	return ret;
}

BOOL WINAPI GetFileVersionInfoExA(_In_ DWORD dwFlags,_In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData)
{
	BOOL ret = ((t_GetFileVersionInfoExA)Version::r_GetFileVersionInfoExA)(dwFlags, lptstrFilename, dwHandle, dwLen, lpData);
	return ret;
}

// WIDE

BOOL WINAPI VerQueryValueW(_In_   LPCVOID pBlock,_In_   LPCWSTR lpSubBlock,_Out_  LPVOID *lplpBuffer,_Out_  PUINT puLen)
{
	return ((t_VerQueryValueW)Version::r_VerQueryValueW)(pBlock, lpSubBlock, lplpBuffer, puLen);
}

BOOL WINAPI GetFileVersionInfoW(_In_ LPCWSTR lptstrFilename,_Reserved_  DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData)
{
	return ((t_GetFileVersionInfoW)Version::r_GetFileVersionInfoW)(lptstrFilename, dwHandle, dwLen, lpData);
}

DWORD WINAPI GetFileVersionInfoSizeW( _In_ LPCWSTR lpSubBlock, _Out_opt_  LPDWORD lpdwHandle)
{
	return ((t_GetFileVersionInfoSizeW)Version::r_GetFileVersionInfoSizeW)(lpSubBlock, lpdwHandle);
}

DWORD WINAPI GetFileVersionInfoSizeExW(_In_ DWORD dwFlags,_In_ LPCWSTR lptstrFilename,_Out_ LPDWORD lpdwHandle)
{
	DWORD ret = ((t_GetFileVersionInfoSizeExW)Version::r_GetFileVersionInfoSizeExW)(dwFlags, lptstrFilename, lpdwHandle);
	return ret;
}

BOOL WINAPI GetFileVersionInfoExW(_In_ DWORD dwFlags,_In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle,_In_ DWORD dwLen,_Out_ LPVOID lpData)
{
	BOOL ret = ((t_GetFileVersionInfoExW)Version::r_GetFileVersionInfoExW)(dwFlags, lptstrFilename, dwHandle, dwLen, lpData);
	return ret;
}