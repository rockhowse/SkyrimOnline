#include <iostream>

#include <Engine/World.h>
#include <Buffer.h>
#include <EnetServer.h>

#include <Engine\Interfaces\IController.h>
#include <Overlay\Chat.h>

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
	SendHello(Logic::Engine::TheController->GetPlayer()->GetName());
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
	SendReliable(0, apPacket);
}

void World::SendHello(const std::string& acPlayerName)
{
	Messages::CliGame_HelloSend* pMessage = new Messages::CliGame_HelloSend;

	pMessage->name = acPlayerName;
	Send(pMessage);
}

void World::SendChatMessage(const std::string& Message)
{
	Messages::CliGame_ChatSend* pMessage = new Messages::CliGame_ChatSend;

	pMessage->message = Message;

	Send(pMessage);
}

void HandleGameCli_HelloRecv(const Messages::GameCli_HelloRecv& aMsg)
{
	std::ostringstream oss;
	oss << "Skyrim Online v" << aMsg.version << " connected.";

	Logic::Engine::TheController->GetUI()->Debug(oss.str());
}

void HandleGameCli_ChatRecv(const Messages::GameCli_ChatRecv& aMsg)
{
	Logic::Overlay::TheChat->AddChatMessage(MyGUI::UString(aMsg.message));
}