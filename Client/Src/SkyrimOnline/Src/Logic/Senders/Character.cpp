#include "stdafx.h"
#include <Logic/NetEngine.hpp>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void NetEngine::SendCharacterInfo(FreeScript::Character& pCharacter)
		{
			Network::Packet data(Opcode::CMSG_CHARACTER_INFO, 0xFFFFFFFF);
			data << pCharacter.GetRace() 
				 << pCharacter.GetGender() 
				 << pCharacter.GetLevel()
				 << pCharacter.GetFaceMorph()
				 << pCharacter.GetAllWornForms()
				 << pCharacter.GetLocationId();
			
			Write(data);
		}
		//--------------------------------------------------------------------------------
		void NetEngine::SendMoveAndLook(FreeScript::Character& pCharacter, uint32_t pDelta)
		{
			Network::Packet data(Opcode::CMSG_MOVE_AND_LOOK, 0xFFFFFFFF);
			data << pCharacter.GetPosX() << pCharacter.GetPosY() << pCharacter.GetPosZ()
				 << pCharacter.GetRotX() << pCharacter.GetRotY() << pCharacter.GetRotZ()
				 << pDelta;

			Write(data);
		}
		//--------------------------------------------------------------------------------
		void NetEngine::SendMount(uint32_t pId)
		{
			Network::Packet mount(Opcode::CMSG_MOUNT_SPAWN, pId);
			Write(mount);
		}
		//--------------------------------------------------------------------------------
		void NetEngine::SendUnmount()
		{
			Network::Packet mount(Opcode::CMSG_MOUNT_REMOVE, 0xFFFFFFFF);
			Write(mount);
		}
		//--------------------------------------------------------------------------------
		void NetEngine::SendEnterRegion(uint32_t pRegion)
		{	
			Network::Packet region(Opcode::CMSG_ENTER_REGION, 0xFFFFFFFF);
			region << pRegion;
			Write(region);
		}
		//--------------------------------------------------------------------------------
	}
}