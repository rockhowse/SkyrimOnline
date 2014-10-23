#include <iostream>

#include "World.h"
#include "Buffer.h"
#include "EnetServer.h"

#include "plugin.h"
#include "skyscript.h"

#include "FreeScript.h"

#include "easylogging++.h"

World::World()
{
	Connect("127.0.0.1", 10578);
}

World::~World()
{
}

void World::OnUpdate()
{
}

void World::OnConnection(uint16_t aConnectionId)
{
	SendHello();
}

void World::OnDisconnection(uint16_t aConnectionId)
{

}

void World::OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer)
{
	uint16_t opcode;
	pBuffer->Read_uint16(opcode);

	m_handler.HandleBuffer(pBuffer, opcode, 0);
}

void World::Send(Packet* apPacket)
{
	SendReliable(0, apPacket);
}

void World::SendHello()
{
	Messages::CliGame_HelloSend pMessage;

	Skyrim::ActorHelper actorHelper(Skyrim::GetPlayer());
	Skyrim::TESNPCHelper npcHelper(actorHelper.GetNpc());

	pMessage.name = npcHelper.GetName();
	Send(&pMessage);
}

void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg)
{
	std::ostringstream oss;
	oss << "Skyrim Online v" << aMsg.version << " connected.";
	Debug::Notification((char*)oss.str().c_str());
}