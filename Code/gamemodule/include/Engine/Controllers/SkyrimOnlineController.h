#pragma once

#include <stdafx.h>

#include <Engine\SkyrimOnline.h>
#include <Engine\Interfaces\IController.h>

namespace GameModule
{
	namespace Engine
	{
		namespace Controllers
		{
			class SkyrimOnlineController : public GameModule::Engine::Interfaces::IController
			{
				public:

				virtual void EnableInput();
				virtual void DisableInput();

				private:

				SkyrimOnline* skyrimOnline = new SkyrimOnline();
			};
		}
	}
}