#include <string>

#define _X86_

#include <windef.h>

extern "C" __declspec(dllimport) FARPROC WINAPI GetProcAddress(__in HMODULE hModule, __in LPCSTR lpProcName);

extern "C" __declspec(dllimport) UINT WINAPI GetSystemDirectoryA(__out_ecount_part_opt(uSize, return +1) LPSTR lpBuffer, __in UINT uSize);

extern "C"__declspec(dllimport) UINT WINAPI GetSystemDirectoryW(__out_ecount_part_opt(uSize, return +1) LPWSTR lpBuffer, __in UINT uSize);

#ifdef UNICODE
	#define GetSystemDirectory  GetSystemDirectoryW
#else
	#define GetSystemDirectory  GetSystemDirectoryA
#endif // !UNICODE

extern "C" __declspec(dllimport) __out_opt HMODULE WINAPI LoadLibraryA(__in LPCSTR lpLibFileName);

extern "C" __declspec(dllimport) __out_opt HMODULE WINAPI LoadLibraryW(__in LPCWSTR lpLibFileName);

#ifdef UNICODE
	#define LoadLibrary  LoadLibraryW
#else
	#define LoadLibrary  LoadLibraryA
#endif // !UNICODE

extern "C" __declspec(dllimport) __declspec(noreturn) VOID WINAPI ExitProcess(__in UINT uExitCode);

typedef BOOL(WINAPI *t_VerQueryValueA)(_In_ LPCVOID pBlock, _In_ LPCTSTR lpSubBlock, _Out_ LPVOID *lplpBuffer, _Out_ PUINT puLen);
typedef BOOL(WINAPI *t_GetFileVersionInfoA)(_In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData);
typedef DWORD(WINAPI *t_GetFileVersionInfoSizeA)(_In_ LPCTSTR lpSubBlock, _Out_opt_ LPDWORD lpdwHandle);
typedef DWORD(WINAPI* t_GetFileVersionInfoSizeExA)(_In_ DWORD dwFlags, _In_ LPCTSTR lptstrFilename, _Out_ LPDWORD lpdwHandle);
typedef BOOL(WINAPI* t_GetFileVersionInfoExA)(_In_ DWORD dwFlags, _In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData);
typedef BOOL(WINAPI *t_VerQueryValueW)(_In_ LPCVOID pBlock, _In_ LPCWSTR lpSubBlock, _Out_ LPVOID *lplpBuffer, _Out_ PUINT puLen);
typedef BOOL(WINAPI *t_GetFileVersionInfoW)(_In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData);
typedef DWORD(WINAPI *t_GetFileVersionInfoSizeW)(_In_ LPCWSTR lpSubBlock, _Out_opt_ LPDWORD lpdwHandle);
typedef DWORD(WINAPI* t_GetFileVersionInfoSizeExW)(_In_ DWORD dwFlags, _In_ LPCWSTR lptstrFilename, _Out_ LPDWORD lpdwHandle);
typedef BOOL(WINAPI* t_GetFileVersionInfoExW)(_In_ DWORD dwFlags, _In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData);

HMODULE module;
t_VerQueryValueA r_VerQueryValueA;
t_VerQueryValueW r_VerQueryValueW;
t_GetFileVersionInfoSizeW r_GetFileVersionInfoSizeW;
t_GetFileVersionInfoSizeA r_GetFileVersionInfoSizeA;
t_GetFileVersionInfoA r_GetFileVersionInfoA;
t_GetFileVersionInfoW r_GetFileVersionInfoW;
t_GetFileVersionInfoSizeExA r_GetFileVersionInfoSizeExA;
t_GetFileVersionInfoSizeExW r_GetFileVersionInfoSizeExW;
t_GetFileVersionInfoExA r_GetFileVersionInfoExA;
t_GetFileVersionInfoExW r_GetFileVersionInfoExW;

std::string GetPath()
{
	char buffer[MAX_PATH];
	// Getting path to system dir and to d3d8.dll
	GetSystemDirectory(buffer, MAX_PATH);
	// Append dll name
	strcat_s(buffer, MAX_PATH, "\\version.dll"); //changed to more secure strcat to prevent buffer overflows, used to be strcat(buffer, "\\version.dll"), change back if desired
	return std::string(buffer);
}

void LoadOriginalDll(void)
{
	if (!module)
		module = LoadLibrary(GetPath().c_str());

	// Debug
	if (!module)
		ExitProcess(0); // exit the hard way
}

void LoadBaseVersion()
{
	LoadOriginalDll();

	r_VerQueryValueA = (t_VerQueryValueA)GetProcAddress(module, "VerQueryValueA");
	r_VerQueryValueW = (t_VerQueryValueW)GetProcAddress(module, "VerQueryValueW");
	r_GetFileVersionInfoA = (t_GetFileVersionInfoA)GetProcAddress(module, "GetFileVersionInfoA");
	r_GetFileVersionInfoW = (t_GetFileVersionInfoW)GetProcAddress(module, "GetFileVersionInfoW");
	r_GetFileVersionInfoSizeA = (t_GetFileVersionInfoSizeA)GetProcAddress(module, "GetFileVersionInfoSizeA");
	r_GetFileVersionInfoSizeW = (t_GetFileVersionInfoSizeW)GetProcAddress(module, "GetFileVersionInfoSizeW");
	r_GetFileVersionInfoSizeExA = (t_GetFileVersionInfoSizeExA)GetProcAddress(module, "GetFileVersionInfoSizeExA");
	r_GetFileVersionInfoSizeExW = (t_GetFileVersionInfoSizeExW)GetProcAddress(module, "GetFileVersionInfoSizeExW");
	r_GetFileVersionInfoExA = (t_GetFileVersionInfoExA)GetProcAddress(module, "GetFileVersionInfoExA");
	r_GetFileVersionInfoExW = (t_GetFileVersionInfoExW)GetProcAddress(module, "GetFileVersionInfoExW");
}

extern "C" BOOL __declspec(dllexport) WINAPI VerQueryValueA(_In_ LPCVOID pBlock, _In_ LPCTSTR lpSubBlock, _Out_ LPVOID *lplpBuffer, _Out_ PUINT puLen)
{
	return r_VerQueryValueA(pBlock, lpSubBlock, lplpBuffer, puLen);
}
extern "C" BOOL __declspec(dllexport) WINAPI GetFileVersionInfoA(_In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData)
{
	return r_GetFileVersionInfoA(lptstrFilename, dwHandle, dwLen, lpData);
}
extern "C" DWORD __declspec(dllexport) WINAPI GetFileVersionInfoSizeA(_In_ LPCTSTR lpSubBlock, _Out_opt_ LPDWORD lpdwHandle)
{
	return r_GetFileVersionInfoSizeA(lpSubBlock, lpdwHandle);
}
extern "C" DWORD __declspec(dllexport) WINAPI GetFileVersionInfoSizeExA(_In_ DWORD dwFlags, _In_ LPCTSTR lptstrFilename, _Out_ LPDWORD lpdwHandle)
{
	return r_GetFileVersionInfoSizeExA(dwFlags, lptstrFilename, lpdwHandle);
}
extern "C" BOOL __declspec(dllexport) WINAPI GetFileVersionInfoExA(_In_ DWORD dwFlags, _In_ LPCTSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData)
{
	return r_GetFileVersionInfoExA(dwFlags, lptstrFilename, dwHandle, dwLen, lpData);
}
// WIDE
extern "C" BOOL __declspec(dllexport) WINAPI VerQueryValueW(_In_ LPCVOID pBlock, _In_ LPCWSTR lpSubBlock, _Out_ LPVOID *lplpBuffer, _Out_ PUINT puLen)
{
	return r_VerQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen);
}
extern "C" BOOL __declspec(dllexport) WINAPI GetFileVersionInfoW(_In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData)
{
	return r_GetFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData);
}
extern "C" DWORD __declspec(dllexport)  WINAPI GetFileVersionInfoSizeW(_In_ LPCWSTR lpSubBlock, _Out_opt_ LPDWORD lpdwHandle)
{
	return r_GetFileVersionInfoSizeW(lpSubBlock, lpdwHandle);
}
extern "C" DWORD __declspec(dllexport) WINAPI GetFileVersionInfoSizeExW(_In_ DWORD dwFlags, _In_ LPCWSTR lptstrFilename, _Out_ LPDWORD lpdwHandle)
{
	return r_GetFileVersionInfoSizeExW(dwFlags, lptstrFilename, lpdwHandle);
}
extern "C" BOOL __declspec(dllexport) WINAPI GetFileVersionInfoExW(_In_ DWORD dwFlags, _In_ LPCWSTR lptstrFilename, _Reserved_ DWORD dwHandle, _In_ DWORD dwLen, _Out_ LPVOID lpData)
{
	return r_GetFileVersionInfoExW(dwFlags, lptstrFilename, dwHandle, dwLen, lpData);
}

#pragma comment(linker, "/EXPORT:VerQueryValueA=_VerQueryValueA@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_VerQueryValueW@16")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_GetFileVersionInfoA@16")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_GetFileVersionInfoW@16")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_GetFileVersionInfoExA@20")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_GetFileVersionInfoExW@20")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_GetFileVersionInfoSizeA@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_GetFileVersionInfoSizeW@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_GetFileVersionInfoSizeExA@12")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_GetFileVersionInfoSizeExW@12")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			LoadBaseVersion();

			LoadLibraryA("d3d9.dll");

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}
	return TRUE;
}