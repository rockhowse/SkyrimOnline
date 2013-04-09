#pragma unmanaged
#define _WIN32_WINNT 0x0501
#define DIRECTINPUT_VERSION 0x0800

#include <fstream>

#include <windows.h>
#include <Winuser.h>
#include <d3d9.h>
#include <dinput.h>

#include <detours.h>

#include <FreeScript/FreeScript.hpp>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )

extern std::ofstream file;