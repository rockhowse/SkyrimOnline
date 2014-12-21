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
			SkyrimUserInterface::SkyrimUserInterface()
			{}

			SkyrimUserInterface::~SkyrimUserInterface()
			{}

			void SkyrimUserInterface::Debug(const std::string& acString)
			{
				Skyrim::Notification(acString);
			}
		}
	}
}