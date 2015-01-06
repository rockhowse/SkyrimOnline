#include "Player.h"
#include "GameServer.h"

#include <easylogging++.h>

Player::Player(uint16_t aPlayerId) : m_connectionId(aPlayerId), m_name("Default")
{
}

Player::~Player()
{
}

void Player::Update()
{

}

uint16_t Player::GetId() const
{
	return m_connectionId;
}

void Player::SetName(const std::string& acName)
{
	m_name = acName;
}

const std::string Player::GetName() const
{
	return m_name;
}

void Player::SendChatSay(const Player* apPlayer, const std::string& acMessage)
{
}

void Player::SendMovementUpdate(const Player* apPlayer)
{
}

void Player::SetMovement(const Messages::Movement& acMovement)
{
	m_movementTracker.Add(acMovement);
}

void Player::SetNpc(const Messages::Npc& acNpc)
{
	m_npc = acNpc;
}

void Player::SetHorse(uint32_t aId)
{
	m_horseId = aId;
}

const Messages::Movement& Player::GetMovement() const
{
	return m_movementTracker.GetLatest();
}

const Messages::Npc& Player::GetNpc() const
{
	return m_npc;
}

uint32_t Player::GetHorse() const
{
	return m_horseId;
}

void HandleCliGame_HelloRecv(const Messages::CliGame_HelloRecv& aMsg)
{
	Player* pPlayer = g_pServer->GetPlayer(aMsg.connectionId);

	if (!pPlayer)
	{
		return;
	}

	std::list<Player*> m_pPlayerList = g_pServer->GetWorld()->GetPlayers();
	std::string pPlayerName = aMsg.name;

	for (Player* p : m_pPlayerList)
	{
		if (p->GetName().compare(aMsg.name) == 0)
		{
			pPlayerName = aMsg.name + "(" + std::to_string(aMsg.connectionId) + ")";
			break;
		}
	}

	LOG(INFO) << "event=hello connection_id=" << aMsg.connectionId << " name=" << pPlayerName;

	pPlayer->SetName(pPlayerName);

	Messages::GameCli_HelloSend* pMessage = new Messages::GameCli_HelloSend;
	pMessage->version = 0;

	g_pServer->Send(aMsg.connectionId, pMessage);
}

void HandleCliGame_PlayerInitializeRecv(const Messages::CliGame_PlayerInitializeRecv& aMsg)
{
	Player* pPlayer = g_pServer->GetPlayer(aMsg.connectionId);
	if (!pPlayer)
	{
		return;
	}

	LOG(INFO) << "event=initialize_player connection_id=" << aMsg.connectionId << " class_id=" << aMsg.player_npc.classId
		<< " race_id=" << aMsg.player_npc.raceId;

	pPlayer->SetNpc(aMsg.player_npc);
	pPlayer->SetHorse(aMsg.horseId);
	pPlayer->SetMovement(aMsg.movement);

	g_pServer->GetWorld()->Enter(pPlayer);
}

void HandleCliGame_PositionRecv(const Messages::CliGame_PositionRecv& aMsg)
{
	Player* pPlayer = g_pServer->GetPlayer(aMsg.connectionId);
	if (!pPlayer)
	{
		return;
	}

	pPlayer->SetMovement(aMsg.movement);
	g_pServer->GetWorld()->UpdateMovement(pPlayer);

	LOG(INFO) << "event=position x=" << aMsg.movement.pos.x << " y=" << aMsg.movement.pos.y << " z=" << aMsg.movement.pos.z
		<< " rot=" << aMsg.movement.rot << " velocity=" << aMsg.movement.velocity << " animation=" << aMsg.movement.animation;
}