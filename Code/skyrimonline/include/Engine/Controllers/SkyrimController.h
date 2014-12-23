#pragma once

#include <stdafx.h>

#include <Engine/Interfaces/IController.h>
#include <skse/GameReferences.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			class SkyrimUserInterface : public Interfaces::IUserInterface
			{
			public:

				SkyrimUserInterface();
				~SkyrimUserInterface();

				void Debug(const std::string& acString);
			};

			class SkyrimPlayer : public Interfaces::IPlayer
			{
			public:

				SkyrimPlayer();
				~SkyrimPlayer();

				const std::string GetName();

			private:

				Actor* m_pPlayer;
			};

			class SkyrimController : public Interfaces::IController
			{
			public:

				SkyrimController();
				~SkyrimController();

				void EnableInput();
				void DisableInput();

				Interfaces::IUserInterface* GetUI();
				Interfaces::IPlayer* GetPlayer();

			private:

				SkyrimUserInterface m_userInterface;
				SkyrimPlayer m_player;

			};
		}
	}
}