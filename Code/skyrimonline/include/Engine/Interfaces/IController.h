#pragma once

#include <stdafx.h>

#include <Buffer.h>
#include <EnetServer.h>

#include <GameCli_Handler.h>

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

				virtual void InitializeServerNode() = 0;

				virtual void PushMovement(const Messages::Movement& acMovement) = 0;
			};

			struct IController
			{
				virtual ~IController() {}

				virtual void EnableInput() = 0;
				virtual void DisableInput() = 0;

				virtual IUserInterface* GetUI() = 0;
				virtual IPlayer* GetLocalPlayer() = 0;
				virtual IPlayer* GetPlayerById(uint16_t aPlayerId) = 0;

				virtual void Update() = 0;

				virtual void Send(Packet* apPacket) = 0;
				virtual void SendReliable(Packet* apPacket) = 0;

				virtual void HandlePlayerAdd(const Messages::GameCli_PlayerAddRecv& acMsg) = 0;
				virtual void HandlePlayerRemove(const Messages::GameCli_PlayerRemoveRecv& acMsg) = 0;
			};
		}

		extern Interfaces::IController* TheController;

	}
}