#include <iostream>

#include <Engine/World.h>
#include <Buffer.h>
#include <EnetServer.h>

#include <Overlay/Chat.h>
//#include <Overlay/ServerConnect.h>

#include "easylogging++.h"

World::World()
{
	Connect();
}

World::~World()
{
}

void World::OnUpdate()
{
}

void World::OnConnection(uint16_t aConnectionId)
{
	SendHello(TheController->GetLocalPlayer()->GetName());
}

void World::OnDisconnection(uint16_t aConnectionId)
{
	//Logic::Engine::TheController->GetUI()->Debug("Connection to the server lost !");
	TheChat->AddChatMessage("Connection to the server lost !");
}

void World::OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer)
{
	uint16_t opcode;
	pBuffer->Read_uint16(opcode);

	m_handler.HandleBuffer(pBuffer, opcode, 0);
}

void World::Connect(const char * addrStr, uint16_t port)
{
	EnetServer::Connect(addrStr, port);
}

void World::Connect()
{
	EnetServer::Connect("127.0.0.1", 10578);
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

	LOG(INFO) << "event=hello state=success version=" << aMsg.version;

	TheChat->AddChatMessage(oss.str());

	TheController->GetLocalPlayer()->InitializeServerNode();
}

void HandleGameCli_ChatRecv(const Messages::GameCli_ChatRecv& aMsg)
{
	LOG(INFO) << "event=chat_recv message=\"" << aMsg.message << "\"";
	TheChat->AddChatMessage(MyGUI::UString(aMsg.message));
}

void HandleGameCli_PositionRecv(const Messages::GameCli_PositionRecv& aMsg)
{
	SkyrimPlayer* pPlayer = TheController->GetPlayerById(aMsg.playerId);
	if (!pPlayer)
	{
		LOG(ERROR) << "event=position player_id=" << aMsg.playerId << " message=\"Player is null\"";
		return;
	}

	pPlayer->PushMovement(aMsg.movement);
}

void HandleGameCli_PlayerAddRecv(const Messages::GameCli_PlayerAddRecv& aMsg)
{
	LOG(INFO) << "event=player_add id=" << aMsg.playerId << " name=" << aMsg.name;
	TheController->HandlePlayerAdd(aMsg);
}

void HandleGameCli_PlayerRemoveRecv(const Messages::GameCli_PlayerRemoveRecv& aMsg)
{
	LOG(INFO) << "event=player_remove id=" << aMsg.playerId;
	TheController->HandlePlayerRemove(aMsg);
}