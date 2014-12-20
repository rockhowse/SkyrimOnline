#pragma once

#include <stdafx.h>

#include <Engine\Controllers\SkyrimOnlineController.h>

namespace GameModule
{
	namespace Engine
	{
		void SkyrimOnlineController::EnableInput()
		{
			skyrimOnline->SetPlayerControls(true);
			skyrimOnline->SetInChargen(false, false, false);
		}

		void SkyrimOnlineController::DisableInput()
		{
			skyrimOnline->SetPlayerControls(false);
			skyrimOnline->SetInChargen(true, true, false);
		}
	}
}