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

	void Connect(const char * addrStr, uint16_t port);
	void Connect();

	void Send(Packet* apPacket);
	void SendReliable(Packet* apPacket);

	void OnUpdate();

	void OnConnection(uint16_t aConnectionId);

	void OnDisconnection(uint16_t aConnectionId);

	void OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer);

private:

	void SendHello(const std::string& acPlayerName);

	std::unique_ptr<EnetServer> m_pConnection;
	Messages::GameCli_Handler m_handler;


};

#endif // WORLD_H