#pragma once

#include <stdafx.h>

#include <Engine\Interfaces\IController.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			class OblivionUserInterface : public Interfaces::IUserInterface
			{
			public:

				OblivionUserInterface();
				~OblivionUserInterface();

				void Debug(const std::string& acString);
			};

			class OblivionPlayer : public Interfaces::IPlayer
			{
			public:

				OblivionPlayer();
				~OblivionPlayer();

				const std::string GetName();
			};

			class OblivionController : public Interfaces::IController
			{
			public:

				OblivionController();
				~OblivionController();

				void EnableInput();
				void DisableInput();

				Interfaces::IUserInterface* GetUI();
				Interfaces::IPlayer* GetPlayer();

			private:

				OblivionUserInterface m_userInterface;
				OblivionPlayer m_player;
			};
		}
	}
}