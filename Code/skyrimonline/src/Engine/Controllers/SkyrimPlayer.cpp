#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <Engine/Controllers/SkyrimHelpers.h>
#include <skyscript.h>
#include <GameForms.h>
#include <GameReferences.h>
#include <GameObjects.h>
#include <GameRTTI.h>
#include <cmath>
#include "easylogging++.h"

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimPlayer::SkyrimPlayer(bool aLocalPlayer)
				: m_pCharacter(nullptr)
				, m_pHorse(nullptr)
				, m_positionTimer(0)
				, m_localPlayer(aLocalPlayer)
			{
				if (m_localPlayer)
				{
					LOG(INFO) << "event=skyrim_player_create type=local";
					m_pCharacter = (Actor*)ScriptDragon::Game::GetPlayer();
				}
				else
				{
					LOG(INFO) << "event=skyrim_player_create type=remote";
				}
			}

			SkyrimPlayer::~SkyrimPlayer()
			{
				LOG(INFO) << "event=skyrim_player_delete";
				if (!m_localPlayer)
				{
					TESNPC* pNpc = (TESNPC*)m_pCharacter->baseForm;

					ScriptDragon::ObjectReference::Disable((ScriptDragon::TESObjectREFR*)m_pCharacter, false);
					ScriptDragon::ObjectReference::Delete((ScriptDragon::TESObjectREFR*)m_pCharacter);

					m_pCharacter = nullptr;
				}
			}

			void SkyrimPlayer::Create(const Messages::GameCli_PlayerAddRecv& acMsg)
			{
				ScriptDragon::TESObjectREFR* pLocalPlayer = (ScriptDragon::TESObjectREFR*)ScriptDragon::Game::GetPlayer();

				Actor* pActor = (Actor*)pLocalPlayer;
				ScriptDragon::TESNPC* pNPC = (ScriptDragon::TESNPC*)pActor->baseForm;
				IFormFactory* pFactory = IFormFactory::GetFactoryForType(kFormType_NPC);
				TESNPC* pNpc = (TESNPC*)pFactory->Create();
				pNpc->CopyFromEx((TESForm*)pNPC);

				Deserialize(pNpc, acMsg.player_npc);

				pNpc->fullName.name = BSFixedString("Lol");

				m_pCharacter = (Actor*)ScriptDragon::ObjectReference::PlaceActorAtMe(pLocalPlayer, (ScriptDragon::TESNPC*)pNpc, 4, NULL);

				m_positionTimer = acMsg.movement.time;
				m_futurePosition = acMsg.movement;

				m_pCharacter->pos.x = m_futurePosition.pos.x;
				m_pCharacter->pos.y = m_futurePosition.pos.y;
				m_pCharacter->pos.z = m_futurePosition.pos.z;
				m_pCharacter->pos.z = m_futurePosition.rot;

				LOG(INFO) << "event=skyrim_player_spawn";
			}

			void SkyrimPlayer::Update(uint32_t aDeltaClock)
			{
				m_positionTimer += aDeltaClock;
				if (m_localPlayer)
				{
					if (m_positionTimer >= kPositionDelay)
					{
						m_positionTimer = 0;
						SendMovementUpdate();
					}
				}
				else
				{
					if (m_positionTimer < m_futurePosition.time)
					{
						// Linear interpolation stuff
						float aLerp = float(aDeltaClock) / (float(m_futurePosition.time - m_positionTimer));
						aLerp = aLerp > 1.0 ? 1.0 : aLerp;
						float bLerp = 1.0f - aLerp;

						m_pCharacter->pos.x = m_pCharacter->pos.x * bLerp + m_futurePosition.pos.x * aLerp;
						m_pCharacter->pos.y = m_pCharacter->pos.y * bLerp + m_futurePosition.pos.y * aLerp;
						m_pCharacter->pos.z = m_pCharacter->pos.z * bLerp + m_futurePosition.pos.z * aLerp;
						m_pCharacter->pos.z = m_pCharacter->rot.y * bLerp + m_futurePosition.rot * aLerp;

						m_positionTimer += aDeltaClock;
						m_positionTimer = m_positionTimer > m_futurePosition.time ? m_futurePosition.time : m_positionTimer;
					}
					else
					{
						m_pCharacter->pos.x = m_futurePosition.pos.x;
						m_pCharacter->pos.y = m_futurePosition.pos.y;
						m_pCharacter->pos.z = m_futurePosition.pos.z;
						m_pCharacter->pos.z = m_futurePosition.rot;
					}
				}
			}

			void SkyrimPlayer::SendMovementUpdate()
			{
				Messages::CliGame_PositionSend* pPacket = new Messages::CliGame_PositionSend;
				pPacket->movement.pos.x = m_pCharacter->pos.x;
				pPacket->movement.pos.y = m_pCharacter->pos.y;
				pPacket->movement.pos.z = m_pCharacter->pos.z;
				pPacket->movement.rot = m_pCharacter->rot.z;
				pPacket->movement.animation = 0;
				pPacket->movement.time = clock();

				BSFixedString speedStr("Speed");
				m_pCharacter->animGraphHolder.GetVariableFloat(&speedStr, &pPacket->movement.velocity);

				TheController->Send(pPacket);
			}

			const std::string SkyrimPlayer::GetName()
			{
				TESNPC* pNpc = DYNAMIC_CAST(m_pCharacter->baseForm, TESForm, TESNPC);
				if (pNpc)
				{
					return pNpc->fullName.name.data;
				}
				return "ERROR";
			}

			void SkyrimPlayer::InitializeServerNode()
			{
				Messages::CliGame_PlayerInitializeSend* pPacket = new Messages::CliGame_PlayerInitializeSend;

				Actor* pHorse = (Actor*)ScriptDragon::Game::GetPlayersLastRiddenHorse();
				pPacket->horseId = pHorse ? pHorse->baseForm->formID : 0;
				
				Serialize((TESNPC*)m_pCharacter->baseForm, pPacket->player_npc);
				pPacket->movement.pos.x = m_pCharacter->pos.x;
				pPacket->movement.pos.y = m_pCharacter->pos.y;
				pPacket->movement.pos.z = m_pCharacter->pos.z;
				pPacket->movement.rot = m_pCharacter->rot.z;
				pPacket->movement.animation = 0;
				pPacket->movement.time = clock();

				BSFixedString speedStr("Speed");
				m_pCharacter->animGraphHolder.GetVariableFloat(&speedStr, &pPacket->movement.velocity);

				TheController->SendReliable(pPacket);

				LOG(INFO) << "event=skyrim_player_initialize";
			}

			void SkyrimPlayer::PushMovement(const Messages::Movement& acMovement)
			{
				if (m_positionTimer > acMovement.time)
				{
					return;
				}
				// If the packet received is more than 1 second ahead in the future, sync to this one
				else if (acMovement.time - m_positionTimer > CLOCKS_PER_SEC)
				{
					// Induce 200ms lag to allow smooth interpolations
					m_positionTimer = acMovement.time - CLOCKS_PER_SEC / 5;
				}

				m_futurePosition = acMovement;
			}
		}
	}
}