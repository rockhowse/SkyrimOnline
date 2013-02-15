#include "stdafx.h"
#include <Game/ActorController.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		ActorController::ActorController(uint32_t pRace, uint32_t pSex)
			: mInit(false), mMe(boost::make_shared<Character>())
		{
		}
		//--------------------------------------------------------------------------------
		ActorController::~ActorController()
		{
			SetMount(0);
		}
		//--------------------------------------------------------------------------------
		boost::shared_ptr<Character> ActorController::GetCharacter()
		{
			return mMe;
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetPosition(float x, float y, float z)
		{
			Vector3 vec = {x,y,z};
			mMe->SetPosition(vec);
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetRotation(float x, float y, float z)
		{
			Vector3 vec = {x,y,z};
			mMe->SetRotation(vec);
		}
		//--------------------------------------------------------------------------------
		void ActorController::InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, uint32_t time)
		{
			SetPosition(posX, posY, posZ);
			SetRotation(rotX, rotY, rotZ);
			mPoint.elapsed = time;
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetMount(uint32_t pMount)
		{
			mMount = pMount;
		}
		//--------------------------------------------------------------------------------
	}
}