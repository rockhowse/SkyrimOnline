#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyscript.h>


SkyrimController* TheController = nullptr;

SkyrimController::SkyrimController()
	: m_player(true)
{
	memset(m_pPlayers, 0, sizeof(SkyrimPlayer*) * (UINT16_MAX + 1));
	m_cachedClock = clock();
	assert(TheController == nullptr);
	TheController = this;
}

SkyrimController::~SkyrimController()
{
	TheController = nullptr;
}

void SkyrimController::Update()
{
	uint32_t deltaClock = clock() - m_cachedClock;
	m_cachedClock = clock();

	m_world.Update();

#ifndef PUBLIC_BUILD
	m_test.Update();
#endif

	m_player.Update(deltaClock);

	for (uint32_t i : m_activeIds)
	{
		SkyrimPlayer* pPlayer = m_pPlayers[i];
		if (pPlayer)
		{
			pPlayer->Update(deltaClock);
		}
	}
}

void SkyrimController::EnableInput()
{
	ScriptDragon::Game::EnablePlayerControls(true, true, true, true, true, true, true, true, 0);
	ScriptDragon::Game::SetInChargen(false, false, false);
}

void SkyrimController::DisableInput()
{
	ScriptDragon::Game::DisablePlayerControls(true, true, true, true, true, true, true, true, 0);
	ScriptDragon::Game::SetInChargen(true, true, false);
}

SkyrimUserInterface* SkyrimController::GetUI()
{
	return &m_userInterface;
}

SkyrimPlayer* SkyrimController::GetLocalPlayer()
{
	return &m_player;
}

SkyrimPlayer* SkyrimController::GetPlayerById(uint16_t aPLayerId)
{
	return m_pPlayers[aPLayerId];
}

void SkyrimController::Send(Packet* apPacket)
{
	m_world.Send(apPacket);
}

void SkyrimController::SendReliable(Packet* apPacket)
{
	m_world.SendReliable(apPacket);
}

void SkyrimController::HandlePlayerAdd(const Messages::GameCli_PlayerAddRecv& acMsg)
{
	if (m_pPlayers[acMsg.playerId])
	{
		ScriptDragon::Debug::ShowMessageBox("Trying to spawn the same player twice !");
	}

	m_pPlayers[acMsg.playerId] = new SkyrimPlayer(false);
	m_pPlayers[acMsg.playerId]->Create(acMsg);
	m_activeIds.push_back(acMsg.playerId);
}

void SkyrimController::HandlePlayerRemove(const Messages::GameCli_PlayerRemoveRecv& acMsg)
{
	m_activeIds.remove(acMsg.playerId);
	delete m_pPlayers[acMsg.playerId];
	m_pPlayers[acMsg.playerId] = nullptr;
}

void SkyrimController::ConnectToWorld(char * addrStr, uint16_t port) {
	m_world.Connect(addrStr, port);
}