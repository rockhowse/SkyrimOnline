#pragma once

#include <stdafx.h>
#include <dllmain.h>

#include <DirectX\DirectXHook.h>

#include <Engine\Input.h>

#include <Overlay\GUI.h>
#include <Overlay\Chat.h>

#include <Engine\Interfaces\IController.h>
#include <Engine\Controllers\SkyrimController.h>
#include <Engine\Controllers\OblivionController.h>

namespace Logic
{
	namespace Engine
	{
		extern "C" __declspec(dllexport) void InitializeGame();
		extern "C" __declspec(dllexport) void Update();
	}
}