#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyrim/SkyrimEngine.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimController::SkyrimController()
			{}

			SkyrimController::~SkyrimController()
			{}

			void SkyrimController::EnableInput()
			{
				Skyrim::SetPlayerControls(true);
				Skyrim::SetInChargen(false, false, false);
			}

			void SkyrimController::DisableInput()
			{
				Skyrim::SetPlayerControls(false);
				Skyrim::SetInChargen(true, true, false);
			}

			Interfaces::IUserInterface* SkyrimController::GetUI()
			{
				return &m_userInterface;
			}

			Interfaces::IPlayer* SkyrimController::GetPlayer()
			{
				return &m_player;
			}
		}
	}
}