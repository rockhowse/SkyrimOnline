#include "stdafx.h"
#include <Game/PlayerEntry.h>
#include <SkyrimOnline.h>
#include <Game/ActorController.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		PlayerEntry::PlayerEntry()
			:
			mPlayer(::Game::GetPlayer()),
			::Game::GOMEntry<FreeScript::Character>(&mPlayer),
			region(std::bind(&FreeScript::Character::GetLocationId, &mPlayer)),
			mount(std::bind(&FreeScript::Character::IsRidding, &mPlayer)),
			pos(std::bind(&FreeScript::Character::GetPosition, &mPlayer)),
			rot(std::bind(&FreeScript::Character::GetRotation, &mPlayer))
		{
		}
		//-------------------------------------------------------------------------------
		void PlayerEntry::Update()
		{
			mPlayer.SetActor(::Game::GetPlayer());
			region(this);
			mount(this);
			pos(this);
			rot(this);
		}
		//--------------------------------------------------------------------------------
		void PlayerEntry::Synchronize()
		{
			region();
			mount();
			pos();
			rot();
		}
		//--------------------------------------------------------------------------------
		void PlayerEntry::Deserialize(const std::string& plainData)
		{
			Framework::Network::Packet packet;
			packet.Initialize(plainData);

			uint8_t flag;
		}
		//--------------------------------------------------------------------------------
		std::string PlayerEntry::Serialize(bool pFull) const
		{
			Framework::Network::Packet packet;

			packet << region.get()
				   << mount.get()
				   << pos.get().x
				   << pos.get().y
				   << pos.get().z
				   << rot.get().x
				   << rot.get().y
				   << rot.get().z;

			return packet.GetBuffer();
		}
		//--------------------------------------------------------------------------------
		bool PlayerEntry::IsDead()
		{
			return mPlayer.IsDead();
		}
		//--------------------------------------------------------------------------------
		FreeScript::Character& PlayerEntry::GetCharacter()
		{
			return mPlayer;
		}
		//--------------------------------------------------------------------------------
	}
}