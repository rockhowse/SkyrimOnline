#include "stdafx.h"
#include <Game/PlayerGOMEntry.h>
#include <Game/PlayerGOMServer.h>
#include <GameWorld.h>
#include <Game/ActorController.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		PlayerGOMEntry::PlayerGOMEntry(Character* character)
			:
			::Game::GOMEntry<Character>(character),
			region(std::bind(&Character::GetLocationId, character)),
			pos(std::bind(&Character::GetPosition, character)),
			rot(std::bind(&Character::GetRotation, character))
		{
		}
		//-------------------------------------------------------------------------------
		PlayerGOMEntry::~PlayerGOMEntry()
		{
		}
		//-------------------------------------------------------------------------------
		void PlayerGOMEntry::Update()
		{
			region(this);
			pos(this);
			rot(this);
		}
		//--------------------------------------------------------------------------------
		void PlayerGOMEntry::Synchronize()
		{
			region();
			pos();
			rot();
		}
		//--------------------------------------------------------------------------------
		void PlayerGOMEntry::SetKey(uint32_t pKey)
		{
			mKey = pKey;
		}
		//--------------------------------------------------------------------------------
		uint32_t PlayerGOMEntry::GetKey() const
		{
			return mKey;
		}
		//--------------------------------------------------------------------------------
		void PlayerGOMEntry::DoDeserialize(const std::string& plainData)
		{
			// SHOULD NEVER BE REACHED

			_trace;
		}
		//--------------------------------------------------------------------------------
		std::string PlayerGOMEntry::DoSerialize(bool pFull) const
		{
			PlayerGOMTransaction transaction;

			if(pFull)
				transaction.SetRace(data->GetRace());
			if(pFull)
				transaction.SetGender(data->GetGender());
			if(pFull)
			{
				transaction.SetFaceMorphs(data->GetFaceMorph());
				transaction.SetWornForms(data->GetAllWornForms());
			}
			if(pFull || pos)
				transaction.SetPosition({{pos.get().x, pos.get().y, pos.get().z}});
			if(pFull || rot)
				transaction.SetRotation({{rot.get().x, rot.get().y, rot.get().z}});

			return transaction.ToPacket().GetBuffer();
		}
		//--------------------------------------------------------------------------------
	}
}