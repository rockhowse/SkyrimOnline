#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "EnetServer.h"
#include "GameCli_Handler.h"
#include <xmemory>

#undef SendMessage

class World : public EnetServer
{
public:

	World();
	~World();

	void SendMessage(Packet* apPacket);
	void SendReliableMessage(Packet* apPacket);

	void OnUpdate();

	void OnConnection(uint16_t aConnectionId);

	void OnDisconnection(uint16_t aConnectionId);

	void OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer);

private:

	void SendHello(const std::string& acPlayerName);
	std::unique_ptr<EnetServer> m_pConnection;
	Messages::GameCli_Handler m_handler;
};

extern World* g_pWorld;

#endif // WORLD_H