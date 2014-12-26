#include "World.h"
#include "Player.h"
#include "GameServer.h"

World::World()
{

}

World::~World()
{
}

void World::Update()
{
	for (auto pPlayer : m_pPlayerList)
	{
		pPlayer->Update();
	}
}

void World::Enter(Player* apPlayer)
{
	for (auto pPlayer : m_pPlayerList)
	{
		Messages::GameCli_PlayerAddSend* apMessage = new Messages::GameCli_PlayerAddSend;
		apMessage->player_npc = apPlayer->GetNpc();
		apMessage->name = apPlayer->GetName();
		apMessage->horseId = apPlayer->GetHorse();
		apMessage->playerId = apPlayer->GetId();
		apMessage->movement = apPlayer->GetMovement();

		g_pServer->SendReliable(pPlayer->GetId(), apMessage);

		apMessage = new Messages::GameCli_PlayerAddSend;
		apMessage->player_npc = pPlayer->GetNpc();
		apMessage->name = pPlayer->GetName();
		apMessage->horseId = pPlayer->GetHorse();
		apMessage->playerId = pPlayer->GetId();
		apMessage->movement = pPlayer->GetMovement();

		g_pServer->SendReliable(apPlayer->GetId(), apMessage);
	}

	m_pPlayerList.push_back(apPlayer);
}

void World::Leave(Player* apPlayer)
{
	m_pPlayerList.remove(apPlayer);

	for (auto pPlayer : m_pPlayerList)
	{
		Messages::GameCli_PlayerRemoveSend* apMessage = new Messages::GameCli_PlayerRemoveSend;
		apMessage->playerId = apPlayer->GetId();

		g_pServer->SendReliable(pPlayer->GetId(), apMessage);
	}
}

void World::UpdateMovement(Player* apPlayer)
{
	for (auto pPlayer : m_pPlayerList)
	{
		if (pPlayer != apPlayer)
		{
			Messages::GameCli_PositionSend* apMessage = new Messages::GameCli_PositionSend;
			apMessage->playerId = apPlayer->GetId();
			apMessage->movement = apPlayer->GetMovement();

			g_pServer->Send(pPlayer->GetId(), apMessage);
		}
	}
}