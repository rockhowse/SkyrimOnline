#pragma once

#include <stdafx.h>

#include <Engine\Controllers\OblivionController.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			OblivionController::OblivionController()
			{}

			OblivionController::~OblivionController()
			{}

			void OblivionController::EnableInput()
			{

			}

			void OblivionController::DisableInput()
			{

			}

			Interfaces::IUserInterface* OblivionController::GetUI()
			{
				return &m_userInterface;
			}

			Interfaces::IPlayer* OblivionController::GetPlayer()
			{
				return &m_player;
			}
		}
	}
}