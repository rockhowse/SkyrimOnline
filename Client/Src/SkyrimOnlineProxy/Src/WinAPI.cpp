#include "stdafx.h"
#include "WinAPI.hpp"


typedef HWND (WINAPI *GetActiveWindow_t)(VOID);
GetActiveWindow_t GetActiveWindow_r;
WNDPROC WindowProc_r = NULL;
HWND first = NULL;
bool active = false;
std::ofstream file("hook.log", std::ios::trunc);

HINSTANCE g_user32 = 0;

void LoadRealUser32Library()
{
	char buffer[MAX_PATH];
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\User32.dll");

	if(!g_user32) g_user32 = ::LoadLibraryA(buffer);
}

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	if(msg == WM_ACTIVATE || msg == WM_KILLFOCUS || msg == WM_ACTIVATEAPP || msg == 641 || msg == 642)
	{
		return 0;
	}
	return CallWindowProc(WindowProc_r, hWindow, msg, wParam, lParam);
}


HWND WINAPI GetActiveWindow_c()
{
	if(WindowProc_r == NULL)
	{
		WindowProc_r = (WNDPROC)SetWindowLong(GetActiveWindow_r(),GWL_WNDPROC,(long)WndProc);
	}
	if(first == NULL)
	{
		first = GetActiveWindow_r();
	}

	if(first != GetActiveWindow_r())
	{
		//SetActiveWindow(first);
		active = true;
	}

	return first;
}

void HookWinAPI()
{
	LoadRealUser32Library();

	PBYTE offset = (PBYTE)GetProcAddress(g_user32, "GetActiveWindow");
	GetActiveWindow_r = (GetActiveWindow_t)DetourFunction(offset, (PBYTE)&GetActiveWindow_c);
}

void ReleaseWinAPI()
{
	if(g_user32)
		::FreeLibrary(g_user32);
}
