#ifndef PLAYER_H
#define PLAYER_H

#include "Movements.h"
#include "CliGame_Handler.h"

class Player
{
public:

	Player(uint16_t aPlayerId);
	~Player();

	void Update();

	// Properties
	uint16_t GetId() const;

	void SetName(const std::string& acName);
	const std::string GetName() const;

	// Senders
	void SendChatSay(const Player* apPlayer, const std::string& acMessage);
	void SendMovementUpdate(const Player* apPlayer);

	// Gameplay
	void SetMovement(const Messages::Movement& acMovement);
	void SetNpc(const Messages::Npc& acNpc);
	void SetHorse(uint32_t aId);

	const Messages::Movement& GetMovement() const;
	const Messages::Npc& GetNpc() const;
	uint32_t GetHorse() const;

private:

	uint16_t m_connectionId;
	std::string m_name;

	// 6 movements will be held at any point in time, ~2 seconds delay
	MovementTracker<6> m_movementTracker;
	Messages::Npc m_npc;
	uint32_t m_horseId;
};

#endif // PLAYER_H