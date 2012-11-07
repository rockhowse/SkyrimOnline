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
			packet.Initialize(plainData.substr(8));

			uint8_t flag = 0;
			packet >> flag;

			if(flag & 0xFF)
			{
				std::vector<float> faceMorph;
				std::vector<uint32_t> wornForms;

				packet >> faceMorph 
			           >> wornForms;

				data->SetFaceMorph(faceMorph);
				data->EquipItems(wornForms);
			}

			uint32_t level, region;
			float px,py,pz,rx,ry,rz;
			bool mount;

			std::string name;

			packet >> level >> region >> mount;
			packet >> px >> py >> pz >> rx >> ry >> rz;

			PlayerGOMServer* gomServer = TheMassiveMessageMgr->GetGOMDatabase()->Get<PlayerGOMServer>();
			gomServer->mControllers[GetKey()]->InterpolateTo(px, py, pz, rx, ry, rz, GetDelta() * 1000);
			
		}
		//--------------------------------------------------------------------------------
		std::string PlayerGOMEntry::DoSerialize(bool pFull) const
		{
			Framework::Network::Packet packet;

			uint8_t flag = 0;
			packet << data->GetRace()
				   << data->GetGender();

			packet << flag;

			if(pFull)
			{
				flag = 0xFF;
				packet << data->GetFaceMorph()
					   << data->GetAllWornForms();
			}

			packet << data->GetLevel()
				   << region.get()
				   << mount.get()
				   << pos.get().x
				   << pos.get().y
				   << pos.get().z
				   << rot.get().x
				   << rot.get().y
				   << rot.get().z;
				  

			packet.Write(&flag, 1, 8);

			return packet.GetBuffer();
		}
		//--------------------------------------------------------------------------------
	}
}