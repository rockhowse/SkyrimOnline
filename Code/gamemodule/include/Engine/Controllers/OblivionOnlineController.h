#pragma once

#include <stdafx.h>

#include <Engine\OblivionOnline.h>
#include <Engine\Interfaces\IController.h>

namespace GameModule
{
	namespace Engine
	{
		namespace Controllers
		{
			class OblivionOnlineController : public GameModule::Engine::Interfaces::IController
			{
				public:

				virtual void EnableInput();
				virtual void DisableInput();
			};
		}
	}
}