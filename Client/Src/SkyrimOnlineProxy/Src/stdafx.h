#pragma once

#define _WIN32_WINNT 0x0501
#define DIRECTINPUT_VERSION 0x0800

#include <boost/signals.hpp>

#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <deque>
#include <concurrent_queue.h>
#include <unordered_map>

#include <windows.h>
#include <Winuser.h>
#include <d3d9.h>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )