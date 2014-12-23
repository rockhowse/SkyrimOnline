#pragma once

#include <stdafx.h>

#include <Buffer.h>
#include <EnetServer.h>

#undef SendMessage

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

				virtual void Update() = 0;

				virtual void SendMessage(Packet* apPacket) = 0;
				virtual void SendReliableMessage(Packet* apPacket) = 0;
			};
		}

		extern Interfaces::IController* TheController;

	}
}