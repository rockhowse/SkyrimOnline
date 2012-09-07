#include "stdafx.h"
#include <Game/SkyrimFormManager.h>
#include <Game/ActorController.h>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		ActorController::ActorController(uint32_t pId, uint32_t pRace, uint32_t pSex)
			:mId(pId), mInit(false)
		{
			TESForm * me = SkyrimFormManager::GetInstance()->GetForm(pRace, pSex);

			mMe = boost::make_shared<Character>(
				(CActor*)ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), me, 1, true, false));
			mMaster = (CActor*)ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), me, 1, true, true);

			Actor::EnableAI(mMe->GetActor(), true);
			Actor::KeepOffsetFromActor(mMe->GetActor(), mMaster, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 20.f, 5.0f);
			Actor::SetActorValue(mMe->GetActor(), "Health", 99999999.f);

			SkyrimOnline::GetInstance().GetAssetManager().Add((TESObjectREFR*)mMe->GetActor());
			SkyrimOnline::GetInstance().GetAssetManager().Add((TESObjectREFR*)mMaster);
		}
		//--------------------------------------------------------------------------------
		ActorController::~ActorController()
		{
			SetMount(0);
			
			SkyrimOnline::GetInstance().GetAssetManager().Remove((TESObjectREFR*)mMe->GetActor());
			SkyrimOnline::GetInstance().GetAssetManager().Remove((TESObjectREFR*)mMaster);

			SkyrimFormManager::GetInstance()->ReleaseForm(ObjectReference::GetBaseObject((TESObjectREFR*)mMe->GetActor()));

			ObjectReference::Delete((TESObjectREFR*)mMe->GetActor());
			ObjectReference::Delete((TESObjectREFR*)mMaster);
		}
		//--------------------------------------------------------------------------------
		boost::shared_ptr<Character> ActorController::GetCharacter()
		{
			return mMe;
		}
		//--------------------------------------------------------------------------------
		uint32_t ActorController::GetId()
		{
			return mId;
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetPosition(float x, float y, float z)
		{
			ObjectReference::SetPosition((TESObjectREFR*)mMaster, x,y,z);
			mMe->SetPos(x,y,z);
			if(mMount)
				mMount->SetPos(x,y,z);
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetRotation(float x, float y, float z)
		{
			ObjectReference::SetAngle((TESObjectREFR*)mMaster, x,y,z);
			mMe->SetRot(x,y,z);
			if(mMount)
				mMount->SetRot(x,y,z);
		}
		//--------------------------------------------------------------------------------
		void ActorController::InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, uint32_t time)
		{
			if(!mInit ||ObjectReference::GetDistance((TESObjectREFR*)mMaster, (TESObjectREFR*)mMe->GetActor()) > 600.f)
			{
				SetPosition(posX, posY, posZ);
				SetRotation(rotX, rotY, rotZ);

				System::Log::Debug(std::to_string((long double)ObjectReference::GetDistance((TESObjectREFR*)mMaster, (TESObjectREFR*)mMe->GetActor())));

				mInit = true;
			}
			ObjectReference::SetPosition((TESObjectREFR*)mMaster, posX,posY,posZ);
			ObjectReference::SetAngle((TESObjectREFR*)mMaster, rotX,rotY,rotZ);
		}
		//--------------------------------------------------------------------------------
		void ActorController::Update(uint32_t elapsed)
		{
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetMount(uint32_t pMount)
		{
			if(mMount)
			{
				SkyrimOnline::GetInstance().GetAssetManager().Remove((TESObjectREFR*)mMount->GetActor());
				ObjectReference::Delete((TESObjectREFR*)mMount->GetActor());
				mMount.reset();
			}
			if(pMount != 0)
			{
				CActor* form =  rtti_cast(ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(pMount), 1, true, false), TESObjectREFR, Actor);
				mMount = boost::make_shared<Character>(form);

				mMount->SetPos(mMe->GetPosX(), mMe->GetPosY(), mMe->GetPosZ());
				mMount->SetRot(mMe->GetRotX(), mMe->GetRotY(), mMe->GetRotZ());

				Actor::EnableAI(mMount->GetActor(), true);

				ObjectReference::TetherToHorse((TESObjectREFR*)mMe->GetActor(), (TESObjectREFR*)mMount->GetActor());
				Actor::KeepOffsetFromActor(mMount->GetActor(), mMaster, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 10.f, 3.f);

				SkyrimOnline::GetInstance().GetAssetManager().Add((TESObjectREFR*)mMount->GetActor());
			}
		}
		//--------------------------------------------------------------------------------
	}
}