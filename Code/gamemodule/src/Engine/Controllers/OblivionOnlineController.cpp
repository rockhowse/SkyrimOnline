#pragma once

#include <stdafx.h>

#include <Engine\Controllers\OblivionOnlineController.h>

namespace GameModule
{
	namespace Engine
	{
		namespace Controllers
		{
			OblivionOnline* oblivionOnline = new OblivionOnline();

			void OblivionOnlineController::EnableInput()
			{
				oblivionOnline->SetPlayerControls();
			}

			void OblivionOnlineController::DisableInput()
			{
				oblivionOnline->SetPlayerControls();
			}
		}
	}
}