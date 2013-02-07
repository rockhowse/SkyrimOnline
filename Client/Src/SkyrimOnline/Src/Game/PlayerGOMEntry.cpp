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
				data->EquipItems(transaction.GetWornForms());
			}
			if(transaction.IsSetFaceMorphs())
			{
				data->SetFaceMorph(transaction.GetFaceMorphs());
			}
			if(transaction.IsSetName())
			{
				data->SetName(transaction.GetName());
			}
			if(transaction.IsSetFacePresets())
			{
				data->SetFacePresets(transaction.GetFacePresets());
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