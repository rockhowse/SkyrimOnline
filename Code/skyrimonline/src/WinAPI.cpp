#include "stdafx.h"
#include "WinAPI.hpp"
#include <skse/Utilities.h>
#include <skse/SafeWrite.h>

typedef HWND(WINAPI *tGetActiveWindow)(void);
tGetActiveWindow GetActiveWindow_RealFunc;
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

HWND WINAPI FakeGetActiveWindow(void)
{
	if (WindowProc_r == NULL)
		WindowProc_r = (WNDPROC)SetWindowLong(GetActiveWindow_RealFunc(), GWL_WNDPROC, (long)WndProc);

	if (hwnd == NULL)
		hwnd = GetActiveWindow_RealFunc();

	if (previous != GetActiveWindow_RealFunc() && hwnd == GetActiveWindow_RealFunc())
	{
		SetCapture(hwnd);
		ShowCursor(FALSE);
	}

	previous = GetActiveWindow_RealFunc();

	return hwnd;
}

void HookWinAPI()
{
	UInt32	thunkAddress = (UInt32)GetIATAddr((UInt8 *)GetModuleHandle(NULL), "user32.dll", "GetActiveWindow");

	GetActiveWindow_RealFunc = (tGetActiveWindow)*(DWORD *)thunkAddress;
	SafeWrite32(thunkAddress, (DWORD)FakeGetActiveWindow);
}

