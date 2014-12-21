#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )

#pragma once
#pragma unmanaged
#define _WIN32_WINNT 0x0501
#define DIRECTINPUT_VERSION 0x0800

#include <fstream>

#include <windows.h>
#include <Winuser.h>
#include <d3d9.h>
#include <dinput.h>

#include <mhook.h>

#include <memory>
#include <xmemory>
#include <stack>
#include <iostream>
#include <string>

#include <list>
#include <vector>
#include <ctime>
#include <deque>
#include <unordered_map>
#include <cstdint>
#include <array>
#include <sstream>
#include <functional>

#include <DInput\Input.hpp>
#include <Directx\myIDirect3D9.h>
#include <Directx\myIDirect3DDevice9.h>