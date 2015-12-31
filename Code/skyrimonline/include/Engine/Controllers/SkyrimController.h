#pragma once

#include <stdafx.h>

#include "SkyrimTest.h"
#include <skse/GameReferences.h>
#include <Engine/World.h>
#include <ctime>

class SkyrimUserInterface
{
public:

	SkyrimUserInterface();
	~SkyrimUserInterface();

	void Debug(const std::string& acString);
};

class SkyrimPlayer
{
public:

	SkyrimPlayer(bool aLocalPlayer = false);
	~SkyrimPlayer();

	void Create(const Messages::GameCli_PlayerAddRecv& acMsg);

	void Update(uint32_t aDeltaClock);

	const std::string GetName();

	void InitializeServerNode();

	void PushMovement(const Messages::Movement& acMovement);

protected:

	void SendMovementUpdate();

private:

	static const uint32_t kPositionDelay = CLOCKS_PER_SEC / 4; // 4 times per second

	Actor* m_pCharacter;
	Actor* m_pHorse;
	clock_t m_positionTimer;
	bool m_localPlayer;

	Messages::Movement m_futurePosition;
};

class SkyrimController
{
public:

	SkyrimController();
	~SkyrimController();
				
	void Update();

	void EnableInput();
	void DisableInput();

	SkyrimUserInterface* GetUI();
	SkyrimPlayer* GetLocalPlayer();
	SkyrimPlayer* GetPlayerById(uint16_t aPLayerId);

	void Send(Packet* apPacket);
	void SendReliable(Packet* apPacket);

	void HandlePlayerAdd(const Messages::GameCli_PlayerAddRecv& acMsg);
	void HandlePlayerRemove(const Messages::GameCli_PlayerRemoveRecv& acMsg);

private:

	SkyrimUserInterface m_userInterface;
	SkyrimPlayer m_player;
	World m_world;

#ifndef PUBLIC_BUILD
	SkyrimTest m_test;
#endif

	clock_t m_cachedClock;

	std::list<uint32_t> m_activeIds;
	SkyrimPlayer* m_pPlayers[UINT16_MAX + 1];
};

extern SkyrimController* TheController;