#include <Game/Service/Time.h>
#include <Game/World.h>
#include <Logic/Session.h>
#include <Network/Packet.h>

namespace Swtor{
namespace Game{
	namespace Service
	{
		//--------------------------------------------------------------------------------
		Time::Time()
		{
		}
		//--------------------------------------------------------------------------------
		uint32_t Time::GetTick()
		{
			return uint32_t(1000);
		}
		//--------------------------------------------------------------------------------
		void Time::Update(float pElapsed)
		{
		}
		//--------------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------------
	void World::SendTimeSync(Logic::Session::pointer pPlayer)
	{
		Network::Packet packet(Opcode::SMSG_GAMEOBJECT, 0xFFFFFFFF);
		packet << "Application_TimeRequester" << mTimeService.GetTick() << (uint64_t)0;

		pPlayer->Write(packet);
	}
	//--------------------------------------------------------------------------------
}
}