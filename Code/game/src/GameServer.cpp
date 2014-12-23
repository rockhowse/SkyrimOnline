#include "GameServer.h"
#include "Player.h"

#include <easylogging++.h>

GameServer* g_pServer = nullptr;

GameServer::GameServer()
    :EnetServer()
{
	std::memset(m_players, 0, sizeof(Player*) * UINT16_MAX);

	long port = 10578;

	Host((uint16_t)port);

	LOG(INFO) << "Server started.";
}

GameServer::~GameServer()
{
}

void GameServer::OnConnection(uint16_t aId)
{
	LOG(INFO) << "Connect : " << aId;

	m_players[aId] = new Player(aId);
}

void GameServer::OnDisconnection(uint16_t aId)
{
	LOG(INFO) << "Disconnect : " << aId;

	delete m_players[aId];
	m_players[aId] = nullptr;
}

void GameServer::OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer)
{
    if (pBuffer->Size() >= 2)
	{
		uint16_t opcode = 0;
		pBuffer->Read_uint16(opcode);

		m_handler.HandleBuffer(pBuffer, opcode, aConnectionId);
	}
}

void GameServer::OnUpdate()
{
}

Player* GameServer::GetPlayer(uint16_t aConnectionId) const
{
	return m_players[aConnectionId];
}

void GameServer::SetPlayerName(uint16_t aConnectionId, const std::string& Name)
{
	m_players[aConnectionId]->SetName(Name);
}

std::string GameServer::GetPlayerName(uint16_t aConnectionId)
{
	return m_players[aConnectionId]->GetName();
}
