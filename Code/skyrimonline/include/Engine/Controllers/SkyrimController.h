#pragma once

#include <stdafx.h>

#include "SkyrimTest.h"
#include <Engine/Interfaces/IController.h>
#include <skse/GameReferences.h>
#include <Engine/World.h>

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

				void InitializeServerNode();

			private:

				Actor* m_pCharacter;
				Actor* m_pHorse;
			};

			class SkyrimController : public Interfaces::IController
			{
			public:

				SkyrimController();
				~SkyrimController();
				
				void Update();

				void EnableInput();
				void DisableInput();

				Interfaces::IUserInterface* GetUI();
				Interfaces::IPlayer* GetLocalPlayer();
				Interfaces::IPlayer* GetPlayerById(uint16_t aPLayerId);


				void Send(Packet* apPacket);
				void SendReliable(Packet* apPacket);

			private:

				SkyrimUserInterface m_userInterface;
				SkyrimPlayer m_player;
				World m_world;
				SkyrimTest m_test;

				SkyrimPlayer* m_pPlayers[UINT16_MAX + 1];

			};
		}
	}
}