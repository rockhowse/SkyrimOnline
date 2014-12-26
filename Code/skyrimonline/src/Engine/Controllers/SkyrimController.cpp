#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyscript.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimController::SkyrimController()
				: m_test()
			{
				memset(m_pPlayers, 0, sizeof(SkyrimPlayer*) * (UINT16_MAX + 1));
			}

			SkyrimController::~SkyrimController()
			{
			}

			void SkyrimController::Update()
			{
				m_world.Update();
				m_test.Update();
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

			Interfaces::IUserInterface* SkyrimController::GetUI()
			{
				return &m_userInterface;
			}

			Interfaces::IPlayer* SkyrimController::GetLocalPlayer()
			{
				return &m_player;
			}

			Interfaces::IPlayer* SkyrimController::GetPlayerById(uint16_t aPLayerId)
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
		}
	}
}