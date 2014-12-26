#include <iostream>

#include <Engine/World.h>
#include <Buffer.h>
#include <EnetServer.h>

#include <Engine\Interfaces\IController.h>
#include <Overlay\Chat.h>

#include "easylogging++.h"

World::World()
{
	Connect("87.98.221.175", 10578);
}

World::~World()
{
}

void World::OnUpdate()
{
}

void World::OnConnection(uint16_t aConnectionId)
{
	SendHello(Logic::Engine::TheController->GetLocalPlayer()->GetName());
}

void World::OnDisconnection(uint16_t aConnectionId)
{
	Logic::Engine::TheController->GetUI()->Debug("Connection to the server lost !");
}

void World::OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer)
{
	uint16_t opcode;
	pBuffer->Read_uint16(opcode);

	m_handler.HandleBuffer(pBuffer, opcode, 0);
}

void World::Send(Packet* apPacket)
{
	EnetServer::Send(0, apPacket);
}

void World::SendReliable(Packet* apPacket)
{
	EnetServer::SendReliable(0, apPacket);
}

void World::SendHello(const std::string& acPlayerName)
{
	Messages::CliGame_HelloSend* pMessage = new Messages::CliGame_HelloSend;

	pMessage->name = acPlayerName;
	SendReliable(pMessage);
}

void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg)
{
	std::ostringstream oss;
	oss << "Skyrim Online v" << aMsg.version << " connected.";

	Logic::Overlay::TheChat->AddChatMessage(oss.str());

	Logic::Engine::TheController->GetLocalPlayer()->InitializeServerNode();
}

void HandleGameCli_ChatRecv(const Messages::GameCli_ChatRecv& aMsg)
{
	Logic::Overlay::TheChat->AddChatMessage(MyGUI::UString(aMsg.message));
}

void HandleGameCli_PositionRecv(const Messages::GameCli_PositionRecv& aMsg)
{

}

void HandleGameCli_PlayerAddRecv(const Messages::GameCli_PlayerAddRecv& aMsg)
{

}

void HandleGameCli_PlayerRemoveRecv(const Messages::GameCli_PlayerRemoveRecv& aMsg)
{

}