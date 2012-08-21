#include <Logic/Session.h>
#include <Logic/World.h>
#include <Game/Character.h>
#include <Game/Mount.h>
#include <System/Tools.h>
#include <Opcodes.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendSpawnPlayer(Session::pointer pPlayer)
		{
			Framework::Network::Packet packet(Opcode::SMSG_PLAYER_SPAWN, pPlayer->GetId());

			packet << pPlayer->GetCharacter().GetRace()
				   << pPlayer->GetCharacter().GetGender()
				   << pPlayer->GetCharacter().GetLevel()
				   << pPlayer->GetCharacter().GetFaceMorph()
				   << pPlayer->GetCharacter().GetWornForms()
				   << pPlayer->GetName();

			Write(packet);

			SendMount(pPlayer);
		}
		//---------------------------------------------------------------------
		void Session::SendMount(Session::pointer pPlayer)
		{
			if(pPlayer->GetCharacter().HasMount())
			{
				Framework::Network::Packet packet(Opcode::SMSG_PLAYER_MOUNT_SPAWN, pPlayer->GetId());
				packet << pPlayer->GetCharacter().GetMount()->GetSkyrimId();
				Write(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::SendUnmount(Session::pointer pPlayer)
		{
			if(pPlayer->GetCharacter().HasMount())
			{
				Framework::Network::Packet packet(Opcode::SMSG_PLAYER_MOUNT_REMOVE, pPlayer->GetId());
				Write(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::SendMoveAndLook(Session::pointer pPlayer)
		{
			Framework::Network::Packet packet(Opcode::SMSG_PLAYER_MOVE_AND_LOOK, pPlayer->GetId());
			packet	<< pPlayer->GetCharacter().Position.x()
					<< pPlayer->GetCharacter().Position.y()
					<< pPlayer->GetCharacter().Position.z()
					<< pPlayer->GetCharacter().Rotation.x()
					<< pPlayer->GetCharacter().Rotation.y()
					<< pPlayer->GetCharacter().Rotation.z()
					<< pPlayer->GetCharacter().mElapsed;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendRemove		(Session::pointer pPlayer)
		{
			Framework::Network::Packet packet(Opcode::SMSG_CHARACTER_REMOVE, pPlayer->GetId());

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendCharacterEnterRegion(uint32_t pId)
		{
			Framework::Network::Packet packet(Opcode::SMSG_CHARACTER_ENTER_AREA, pId);
			packet << (uint32_t)1;
			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}