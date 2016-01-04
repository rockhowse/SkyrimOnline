#include "GameServer.h"
#include "Player.h"

#include <easylogging++.h>

GameServer* g_pServer = nullptr;


GameServer::GameServer()
    :EnetServer()
{
	std::memset(m_players, 0, sizeof(Player*) * (UINT16_MAX +1 ));

	Host();
	LOG(INFO) << "event=server_state value=started";

	// hard coding version for now
	LOG(INFO) << "Version v0.0.3";
}

GameServer::~GameServer()
{
	LOG(INFO) << "event=server_state value=stopped";
}

void GameServer::OnConnection(uint16_t aId)
{
	LOG(INFO) << "event=connected connection_id=" << aId;

	m_players[aId] = new Player(aId);
}

void GameServer::OnDisconnection(uint16_t aId)
{
	LOG(INFO) << "event=disconnected connection_id=" << aId;

	m_world.Leave(m_players[aId]);

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
	m_world.Update();
}

Player* GameServer::GetPlayer(uint16_t aConnectionId) const
{
	return m_players[aConnectionId];
}

World* GameServer::GetWorld()
{
	return &m_world;
}
