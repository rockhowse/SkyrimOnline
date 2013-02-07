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
			::Game::GOMEntry<FreeScript::Character>(character)
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
		}
		//--------------------------------------------------------------------------------
		void PlayerGOMEntry::Synchronize()
		{
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

			if(transaction.IsSetWornForms())
			{
				//data->EquipItems(transaction.GetWornForms());
				Framework::System::Log::Debug("Worn forms is set");
			}
			if(transaction.IsSetFaceMorphs())
			{
				//data->SetFaceMorph(transaction.GetFaceMorphs());
				Framework::System::Log::Debug("Face morphs is set");
			}
			if(transaction.IsSetName())
			{
				//data->SetName(transaction.GetName());
				Framework::System::Log::Debug("Name is set");
			}
			if(transaction.IsSetFacePresets())
			{
				//data->SetFacePresets(transaction.GetFacePresets());
				Framework::System::Log::Debug("Face presets is set");
			}
			if(transaction.IsSetRotation())
			{
				BasicArray<3, float> rotation = transaction.GetRotation();
				Framework::System::Log::Debug("Rotation is set");
			}
			if(transaction.IsSetPosition())
			{
				BasicArray<3, float> position = transaction.GetPosition();
				Framework::System::Log::Debug("Position is set");
			}

		}
		//--------------------------------------------------------------------------------
		std::string PlayerGOMEntry::DoSerialize(bool pFull) const
		{
			assert(false);

			return "";
		}
		//--------------------------------------------------------------------------------
	}
}