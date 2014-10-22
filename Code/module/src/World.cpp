#include <iostream>

#include "World.h"
#include "Buffer.h"
#include "BoostManager.h"
#include "BoostServer.h"

#include "plugin.h"
#include "skyscript.h"

#include "easylogging++.h"

World::World()
{
	m_pConnection.reset(new BoostConnection(BoostManager::GetInstance().GetIoService(), 0));
	m_pConnection->Connect("127.0.0.1", 10578);
}

World::~World()
{
}

void World::Update()
{
	if (m_pConnection)
	{
		ReadBuffer* pBuffer = nullptr;
		while (m_pConnection->Consume(pBuffer))
		{
			if (pBuffer == nullptr)
			{
				SendHello();
			}
			else
			{
				uint16_t opcode;
				pBuffer->Read_uint16(opcode);

				m_handler.HandleBuffer(pBuffer, opcode, 0);
			}
		}
	}
}

void World::Send(Packet* apPacket)
{
	m_pConnection->Write(BoostServer::Serialize(apPacket));
}

void World::SendHello()
{
	Messages::CliGame_HelloSend pMessage;
	pMessage.name = "toto";
	Send(&pMessage);
}

void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg)
{
	LOG(INFO) << aMsg.version;
}