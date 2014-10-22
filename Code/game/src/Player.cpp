#include "Player.h"
#include "GameServer.h"

#include <easylogging++.h>

Player::Player(uint16_t aPlayerId)
	: m_connectionId(aPlayerId)
	, m_name("Default")
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

void Player::SetMovement(const Movement& acMovement)
{
	m_movementTracker.Add(acMovement);
}

void HandleCliGame_HelloRecv(const Messages::CliGame_HelloRecv& aMsg)
{
	LOG(INFO) << aMsg.connectionId << " " << aMsg.name;

	Messages::GameCli_HelloSend* pMessage = new Messages::GameCli_HelloSend;
	pMessage->version = 0;

	g_pServer->Send(aMsg.connectionId, pMessage);
}