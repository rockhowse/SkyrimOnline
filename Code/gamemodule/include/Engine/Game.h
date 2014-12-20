#pragma once

#include <stdafx.h>
#include <dllmain.h>

#include <DirectX\DirectXHook.h>
#include <Engine\SkyrimOnline.h>
#include <Engine\OblivionOnline.h>

#include <Overlay\GUI.h>
#include <Overlay\Chat.h>

#include <Engine\Interfaces\IController.h>
#include <Engine\Controllers\SkyrimOnlineController.h>
#include <Engine\Controllers\OblivionOnlineController.h>

namespace GameModule
{
	namespace Engine
	{
		extern "C" __declspec(dllexport) void InitializeGame();

		GameModule::Engine::Interfaces::IController* iController;
	}
}