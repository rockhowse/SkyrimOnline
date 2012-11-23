#include "stdafx.h"
#include "SkyrimFormManager.h"
#include <GameWorld.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		SkyrimFormManager* SkyrimFormManager::mInstance = nullptr;
		//--------------------------------------------------------------------------------
		SkyrimFormManager::SkyrimFormManager()
			:mBaseAddr(0)
		{
			for(uint32_t i = 0; i < 100; ++i)
			{
				mUsedOffsets[i] = false;
			}

			for(uint32_t i = 0, size = FreeScript::TESDataHandler::GetInstance()->mNpcs.size; i != size; ++i)
			{
				auto npc = FreeScript::TESDataHandler::GetInstance()->mNpcs[i];
				if(FreeScript::TESNPCHelper(npc).GetName().find("SkyrimOnlineBaseAddr") != std::string::npos)
				{
					mBaseAddr = npc->formID + 1; 
				}
			}

			if(mBaseAddr == 0)
			{
				System::Log::Debug("Unable to find the base address, enable SkyrimOnline.esp");
				System::Log::Flush();

				Debug::ShowMessageBox("I need SkyrimOnline.esp to run, please restart the game and enable it !");
				delete TheGameWorld;
				*((int*)0) = 4;

				return;
			}
			std::ostringstream os;
			os << "Base address at : 0x" << std::hex << mBaseAddr;
			System::Log::Debug(os.str());
		}
		//--------------------------------------------------------------------------------
		SkyrimFormManager::~SkyrimFormManager()
		{
		}
		//--------------------------------------------------------------------------------
		SkyrimFormManager* SkyrimFormManager::GetInstance()
		{
			if(mInstance == nullptr)
				mInstance = new SkyrimFormManager;
			return mInstance;
		}
		//--------------------------------------------------------------------------------
		TESForm* SkyrimFormManager::GetForm(uint32_t pRace, uint32_t pGender)
		{
			uint32_t offset = 0;
			for(offset = 0; mUsedOffsets[offset] == true && offset < 100; ++offset);

			if(mUsedOffsets[offset] == false)
			{
				uint32_t actorId = ID_TESNPC::BretonMalePreset10;
				if(pGender == 0)
				{
					switch(pRace)
					{
					case FreeScript::TESRace::Altmer: actorId = ID_TESNPC::HighElfMalePreset10; break;
					case FreeScript::TESRace::Bosmer: actorId = ID_TESNPC::WoodElfMalePreset10; break;
					case FreeScript::TESRace::Argorian: actorId = ID_TESNPC::ArgonianMalePreset10; break;
					case FreeScript::TESRace::Dunmer: actorId = ID_TESNPC::DarkElfMalePreset10; break;
					case FreeScript::TESRace::Imperial: actorId = ID_TESNPC::ImperialMalePreset10; break;
					case FreeScript::TESRace::Khajiit: actorId = ID_TESNPC::KhajiitMalePreset10; break;
					case FreeScript::TESRace::Nord: actorId = ID_TESNPC::NordMalePreset10; break;
					case FreeScript::TESRace::Orc: actorId = ID_TESNPC::OrcMalePreset10; break;
					case FreeScript::TESRace::Redguard: actorId = ID_TESNPC::RedguardMalePreset10; break;
					}
				}
				else
				{
					actorId = ID_TESNPC::BretonFemalePreset10;
					switch(pRace)
					{
					case FreeScript::TESRace::Altmer: actorId = ID_TESNPC::HighElfFemalePreset10; break;
					case FreeScript::TESRace::Bosmer: actorId = ID_TESNPC::WoodElfFemalePreset10; break;
					case FreeScript::TESRace::Argorian: actorId = ID_TESNPC::ArgonianFemalePreset10; break;
					case FreeScript::TESRace::Dunmer: actorId = ID_TESNPC::DarkElfFemalePreset10; break;
					case FreeScript::TESRace::Imperial: actorId = ID_TESNPC::ImperialFemalePreset10; break;
					case FreeScript::TESRace::Khajiit: actorId = ID_TESNPC::KhajiitFemalePreset10; break;
					case FreeScript::TESRace::Nord: actorId = ID_TESNPC::NordFemalePreset10; break;
					case FreeScript::TESRace::Orc: actorId = ID_TESNPC::OrcFemalePreset10; break;
					case FreeScript::TESRace::Redguard: actorId = ID_TESNPC::RedguardFemalePreset10; break;
					}
				}
				TESForm* form = ::Game::GetFormById(mBaseAddr + offset);
				//TESForm* baseForm = ::Game::GetFormById(actorId);

				TESNPC* npc = rtti_cast(form, TESForm, TESNPC);
				//TESNPC* baseNpc = rtti_cast(baseForm, TESForm, TESNPC);

				npc->formID = mBaseAddr + offset;

				mUsedOffsets[offset] = true;

				return form;
			}
			return nullptr;
		}
		//--------------------------------------------------------------------------------
		void SkyrimFormManager::ReleaseForm(TESForm* pForm)
		{
			uint32_t offset = pForm->formID - mBaseAddr;
			if(offset < 100)
				mUsedOffsets[offset] = false;
		}
		//--------------------------------------------------------------------------------
	}
}