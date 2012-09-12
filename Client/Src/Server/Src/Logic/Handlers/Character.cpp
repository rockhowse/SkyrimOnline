#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <Opcodes.h>

using namespace Framework;

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandlePositionAndLook(Framework::Network::Packet& pData)
		{
			float tmp;
			pData >> tmp;
			GetCharacter().Position.setX(tmp);
			pData >> tmp;
			GetCharacter().Position.setY(tmp);
			pData >> tmp;
			GetCharacter().Position.setZ(tmp);
			pData >> tmp;
			GetCharacter().Rotation.setX(tmp);
			pData >> tmp;
			GetCharacter().Rotation.setY(tmp);
			pData >> tmp;
			GetCharacter().Rotation.setZ(tmp);
			pData >> GetCharacter().mElapsed;

			auto region = mWorld->GetMap()->GetRegion(mRegion);
			if(region)
				region->BroadcastMoveAndLook(shared_from_this());
		}
		//---------------------------------------------------------------------
		void Session::HandlePlayerEvent(Session::pointer pPlayer)
		{
		}
		//---------------------------------------------------------------------
		void Session::HandleMount(Framework::Network::Packet& pData)
		{
			if(pData.ObjectId != 0)
			{
				GetCharacter().SetMount(pData.ObjectId);
				Framework::Network::Packet packet(Opcode::SMSG_PLAYER_MOUNT_SPAWN, GetId());
				packet << pData.ObjectId;
				Broadcast(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleUnmount(Framework::Network::Packet& pData)
		{
			GetCharacter().SetMount(0);
			Framework::Network::Packet packet(Opcode::SMSG_PLAYER_MOUNT_REMOVE, GetId());
			Broadcast(packet);
		}
		//---------------------------------------------------------------------
		void Session::HandleCharacterInfo(Framework::Network::Packet& pData)
		{
			pData	>> mCharacter.mRace
				    >> mCharacter.mGender
				    >> mCharacter.mLevel
					>> mCharacter.mFaceMorph
					>> mCharacter.mWornForms
					>> mRegion;

			mWorld->GetMap()->EnterRegion(mRegion, shared_from_this());

		}
		//---------------------------------------------------------------------
		void Session::HandleEnterRegion(Framework::Network::Packet& pData)
		{
			mWorld->GetMap()->LeaveRegion(mRegion, shared_from_this());
			pData >> mRegion;
			mWorld->GetMap()->EnterRegion(mRegion, shared_from_this());
		}
		//---------------------------------------------------------------------
		float Session::GetDistance(Session::pointer pPlayer)
		{
			return pPlayer->GetCharacter().Position.distance(GetCharacter().Position);
		}
		//---------------------------------------------------------------------
	}
}