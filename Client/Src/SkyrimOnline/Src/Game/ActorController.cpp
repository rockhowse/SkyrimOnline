#include "stdafx.h"
#include <Game/SkyrimFormManager.h>
#include <Game/ActorController.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		ActorController::ActorController(uint32_t pRace, uint32_t pSex)
			: mInit(false)
		{
			TESForm * me = SkyrimFormManager::GetInstance()->GetForm(pRace, pSex);

			mMe = boost::make_shared<FreeScript::Character>(
				(Actor*)ObjectReference::PlaceAtMe((TESObjectREFR*)FreeScript::Game::GetPlayer(), me, 1, true, false));
			mMaster = (Actor*)ObjectReference::PlaceAtMe((TESObjectREFR*)FreeScript::Game::GetPlayer(), me, 1, true, true);

			SActor::EnableAI(mMe->GetActor(), true);
			SActor::KeepOffsetFromActor(mMe->GetActor(), mMaster, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 20.f, 5.0f);
			SActor::SetActorValue(mMe->GetActor(), "Health", 99999999.f);

			TheGameWorld->GetAssetManager().Add((TESObjectREFR*)mMe->GetActor());
			TheGameWorld->GetAssetManager().Add((TESObjectREFR*)mMaster);
		}
		//--------------------------------------------------------------------------------
		ActorController::~ActorController()
		{
			SetMount(0);
			
			TheGameWorld->GetAssetManager().Remove((TESObjectREFR*)mMe->GetActor());
			TheGameWorld->GetAssetManager().Remove((TESObjectREFR*)mMaster);

			SkyrimFormManager::GetInstance()->ReleaseForm(mMe->GetActor()->baseForm);

			ObjectReference::Delete((TESObjectREFR*)mMe->GetActor());
			ObjectReference::Delete((TESObjectREFR*)mMaster);

			uint32_t id = mMe->GetActor()->formID,
				id2 = mMaster->formID;

			FreeScript::TESObjectCELL* cell = mMe->GetActor()->parentCell;

			for(uint32_t i = 0; i != cell->childList.size; ++i)
			{
				if(cell->childList[i]->formID == id || cell->childList[i]->formID == id2)
				{
					cell->childList.Remove(i);
					i = 0;
				}
			}

			_trace
		}
		//--------------------------------------------------------------------------------
		boost::shared_ptr<FreeScript::Character> ActorController::GetCharacter()
		{
			return mMe;
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
			if(!mInit || ObjectReference::GetDistance((TESObjectREFR*)mMaster, (TESObjectREFR*)mMe->GetActor()) > 600.f)
			{
				SetPosition(posX, posY, posZ);
				SetRotation(rotX, rotY, rotZ);

				mInit = true;
			}
			ObjectReference::SetPosition((TESObjectREFR*)mMaster, posX,posY,posZ);
			ObjectReference::SetAngle((TESObjectREFR*)mMaster, rotX,rotY,rotZ);
		}
		//--------------------------------------------------------------------------------
		void ActorController::SetMount(uint32_t pMount)
		{
			if(mMount)
			{
				TheGameWorld->GetAssetManager().Remove((TESObjectREFR*)mMount->GetActor());
				ObjectReference::Delete((TESObjectREFR*)mMount->GetActor());
				mMount.reset();
			}
			if(pMount != 0)
			{
				Actor* form =  rtti_cast(ObjectReference::PlaceAtMe((TESObjectREFR*)FreeScript::Game::GetPlayer(), FreeScript::Game::GetForm(pMount), 1, true, false), TESObjectREFR, Actor);
				mMount = boost::make_shared<FreeScript::Character>(form);

				mMount->SetPos(mMe->GetPosX(), mMe->GetPosY(), mMe->GetPosZ());
				mMount->SetRot(mMe->GetRotX(), mMe->GetRotY(), mMe->GetRotZ());

				SActor::EnableAI(mMount->GetActor(), true);

//				ObjectReference::TetherToHorse((TESObjectREFR*)mMe->GetActor(), (TESObjectREFR*)mMount->GetActor());
				SActor::KeepOffsetFromActor(mMount->GetActor(), mMaster, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 10.f, 3.f);

				TheGameWorld->GetAssetManager().Add((TESObjectREFR*)mMount->GetActor());
			}
		}
		//--------------------------------------------------------------------------------
	}
}