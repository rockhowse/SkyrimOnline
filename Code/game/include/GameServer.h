#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "BoostServer.h"
#include "BoostManager.h"
#include <cstdint>

class Player;

class GameServer : public BoostServer
{
public:

    GameServer();
    ~GameServer();

    void OnUpdate();
    void OnConnection(uint16_t aConnectionId);
    void OnDisconnection(uint16_t aConnectionId);
	void OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer);

	Player* GetPlayer(uint16_t aConnectionId) const;

private:

	Player* m_players[UINT16_MAX];
};

extern GameServer* g_pServer;

#endif // GAME_SERVER_H