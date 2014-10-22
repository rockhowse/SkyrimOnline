#ifndef WORLD_H
#define WORLD_H

#pragma once

#include "BoostConnection.h"
#include "GameCli_Handler.h"
#include <xmemory>

class World
{
public:

	World();
	~World();

	void Update();

	void Send(Packet* apPacket);

private:

	void SendHello();

	std::unique_ptr<BoostConnection> m_pConnection;
	Messages::GameCli_Handler m_handler;
};

extern World* g_pWorld;

#endif // WORLD_H