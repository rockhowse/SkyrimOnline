#include "stdafx.h"
#include "WinAPI.hpp"

#pragma unmanaged

typedef HWND(WINAPI *GetActiveWindow_t)(void);
GetActiveWindow_t GetActiveWindow_r;
WNDPROC WindowProc_r = NULL;
HWND hwnd = NULL, previous = NULL;
bool active = false, isHooked = false;

HINSTANCE g_user32 = 0;

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_ACTIVATE || msg == WM_KILLFOCUS || msg == WM_ACTIVATEAPP || msg == 641 || msg == 642)
		return 0;

	return CallWindowProc(WindowProc_r, hWindow, msg, wParam, lParam);
}

HWND WINAPI GetActiveWindow_c(void)
{
	if (WindowProc_r == NULL)
		WindowProc_r = (WNDPROC)SetWindowLong(GetActiveWindow_r(), GWL_WNDPROC, (long)WndProc);

	if (hwnd == NULL)
		hwnd = GetActiveWindow_r();

	if (previous != GetActiveWindow_r() && hwnd == GetActiveWindow_r())
	{
		//SetForegroundWindow(first);
		SetCapture(hwnd);
		ShowCursor(FALSE);
	}

	previous = GetActiveWindow_r();

	return hwnd;
}

void HookWinAPI()
{
	if (!g_user32)
		g_user32 = ::LoadLibraryA("user32.dll");

	GetActiveWindow_r = (GetActiveWindow_t)GetProcAddress(g_user32, "GetActiveWindow");
	Mhook_SetHook((PVOID*)&GetActiveWindow_r, GetActiveWindow_c);
}

void ReleaseWinAPI()
{
	if (g_user32)
		::FreeLibrary(g_user32);

	Mhook_Unhook((PVOID*)GetActiveWindow_c);
}
