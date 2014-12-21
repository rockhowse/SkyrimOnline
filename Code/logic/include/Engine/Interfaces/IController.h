#pragma once

#include <stdafx.h>

namespace Logic
{
	namespace Engine
	{
		namespace Interfaces
		{
			struct IUserInterface
			{
				virtual ~IUserInterface() {}

				virtual void Debug(const std::string& acString) = 0;
			};

			struct IPlayer
			{
				virtual ~IPlayer() {}

				virtual const std::string GetName() = 0;
			};

			struct IController
			{
				virtual ~IController() {}

				virtual void EnableInput() = 0;
				virtual void DisableInput() = 0;;

				virtual IUserInterface* GetUI() = 0;
				virtual IPlayer* GetPlayer() = 0;
			};
		}

		extern Interfaces::IController* TheController;
	}
}