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
		PlayerGOMEntry::PlayerGOMEntry(FreeScript::Character* character)
			:
			::Game::GOMEntry<FreeScript::Character>(character),
			region(std::bind(&FreeScript::Character::GetLocationId, character)),
			mount(std::bind(&FreeScript::Character::IsRidding, character)),
			pos(std::bind(&FreeScript::Character::GetPosition, character)),
			rot(std::bind(&FreeScript::Character::GetRotation, character))
		{
		}
		//-------------------------------------------------------------------------------
		PlayerGOMEntry::~PlayerGOMEntry()
		{
			delete data;
		}
		//-------------------------------------------------------------------------------
		void PlayerGOMEntry::Update()
		{
			region(this);
			mount(this);
			pos(this);
			rot(this);
		}
		//--------------------------------------------------------------------------------
		void PlayerGOMEntry::Synchronize()
		{
			region();
			mount();
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
			Framework::Network::Packet packet;
			packet.Initialize(plainData);

			PlayerGOMTransaction transaction;
			packet >> transaction;

			PlayerGOMServer* gomServer = TheMassiveMessageMgr->GetGOMDatabase()->Get<PlayerGOMServer>();
			auto controller = gomServer->mControllers[GetKey()]; 
			//controller->InterpolateTo(px, py, pz, rx, ry, rz, GetDelta() * 1000);
			
		}
		//--------------------------------------------------------------------------------
		std::string PlayerGOMEntry::DoSerialize(bool pFull) const
		{
// NOTE THIS CODE SHOULD NEVER BE REACHED

			assert(false);

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