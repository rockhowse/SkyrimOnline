#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "EnetServer.h"
#include "GameCli_Handler.h"
#include <xmemory>

class World : public EnetServer
{
public:

	World();
	~World();

	void Send(Packet* apPacket);

	void OnUpdate();

	void OnConnection(uint16_t aConnectionId);

	void OnDisconnection(uint16_t aConnectionId);

	void OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer);

private:

	void SendHello();

	std::unique_ptr<EnetServer> m_pConnection;
	Messages::GameCli_Handler m_handler;
};

extern World* g_pWorld;

#endif // WORLD_H