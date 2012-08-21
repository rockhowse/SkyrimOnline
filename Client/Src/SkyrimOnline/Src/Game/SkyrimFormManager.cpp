#include "stdafx.h"
#include "SkyrimFormManager.h"
#include <SkyrimOnline.h>
#include <Data/NpcList.h>

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

			for(auto itor = Data::NpcList::begin(); itor != Data::NpcList::end(); ++itor)
			{
				if(SkyrimScript::NpcGetName(*itor).find("SkyrimOnlineBaseAddr") != std::string::npos)
				{
					mBaseAddr = Form::GetFormID((TESForm*)*itor) + 1; 
				}

			}
			if(mBaseAddr == 0)
			{
				System::Log::Debug("Unable to find the base address, enable SkyrimOnline.esp");
				System::Log::Flush();

				Debug::ShowMessageBox("I need SkyrimOnline.esp to run, please restart the game and enable it !");
				SkyrimOnline::Stop();

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
					case Skyrim::Race::Altmer: actorId = ID_TESNPC::HighElfMalePreset10; break;
					case Skyrim::Race::Bosmer: actorId = ID_TESNPC::WoodElfMalePreset10; break;
					case Skyrim::Race::Argorian: actorId = ID_TESNPC::ArgonianMalePreset10; break;
					case Skyrim::Race::Dunmer: actorId = ID_TESNPC::DarkElfMalePreset10; break;
					case Skyrim::Race::Imperial: actorId = ID_TESNPC::ImperialMalePreset10; break;
					case Skyrim::Race::Khajiit: actorId = ID_TESNPC::KhajiitMalePreset10; break;
					case Skyrim::Race::Nord: actorId = ID_TESNPC::NordMalePreset10; break;
					case Skyrim::Race::Orc: actorId = ID_TESNPC::OrcMalePreset10; break;
					case Skyrim::Race::Redguard: actorId = ID_TESNPC::RedguardMalePreset10; break;
					}
				}
				else
				{
					actorId = ID_TESNPC::BretonFemalePreset10;
					switch(pRace)
					{
					case Skyrim::Race::Altmer: actorId = ID_TESNPC::HighElfFemalePreset10; break;
					case Skyrim::Race::Bosmer: actorId = ID_TESNPC::WoodElfFemalePreset10; break;
					case Skyrim::Race::Argorian: actorId = ID_TESNPC::ArgonianFemalePreset10; break;
					case Skyrim::Race::Dunmer: actorId = ID_TESNPC::DarkElfFemalePreset10; break;
					case Skyrim::Race::Imperial: actorId = ID_TESNPC::ImperialFemalePreset10; break;
					case Skyrim::Race::Khajiit: actorId = ID_TESNPC::KhajiitFemalePreset10; break;
					case Skyrim::Race::Nord: actorId = ID_TESNPC::NordFemalePreset10; break;
					case Skyrim::Race::Orc: actorId = ID_TESNPC::OrcFemalePreset10; break;
					case Skyrim::Race::Redguard: actorId = ID_TESNPC::RedguardFemalePreset10; break;
					}
				}
				TESForm* form = ::Game::GetFormById(mBaseAddr + offset);
				std::ostringstream os;
				mUsedOffsets[offset] = true;

				return ::Game::GetFormById(actorId);
			}
			return nullptr;
		}
		//--------------------------------------------------------------------------------
		void SkyrimFormManager::ReleaseForm(TESForm* pForm)
		{
			uint32_t offset = Form::GetFormID(pForm) - mBaseAddr;
			if(offset < 100)
				mUsedOffsets[offset] = false;
		}
		//--------------------------------------------------------------------------------
	}
}