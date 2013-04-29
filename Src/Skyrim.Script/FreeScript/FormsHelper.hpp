#pragma once

#include "Forms.hpp"
#include "Common.hpp"
#include <sstream>
#include <vector>

namespace FreeScript
{
	class TESNPCHelper : public BaseHelper<TESNPC>
	{
	public:

		TESNPCHelper(TESNPC* ptr) : BaseHelper<TESNPC>(ptr){};

		uint32_t GetRaceID()
		{
			return mData->race.race->formID;
		}

		TESRace* GetRace()
		{
			return mData->race.race;
		}

		void SetRace(TESRace* pRace)
		{
			mData->race.race = pRace;
		}

		std::string GetDebugName()
		{			
			if(mData)
			{
				std::ostringstream os;
				os << std::hex << mData->formID << " " << GetName();
				return os.str();
			}
			return "";
		}

		std::string GetName()
		{			
			if(mData)
				return std::string(mData->fullName.name.data);
			return "";
		}

		void GetFaceMorph(std::vector<float>& pMorphOptions)
		{
			pMorphOptions.clear();
			pMorphOptions.assign(mData->faceMorph->option, mData->faceMorph->option + TESNPC::FaceMorphs::OptionCount);
		}

		void SetFaceMorph(const std::vector<float>& pMorphOptions)
		{
			for(uint32_t i = 0; i < pMorphOptions.size(); ++i)
				mData->faceMorph->option[i] = pMorphOptions[i];
		}

		void GetFacePresets(std::vector<uint32_t>& pMorphOptions)
		{
			pMorphOptions.clear();
			pMorphOptions.assign(mData->faceMorph->presets, mData->faceMorph->presets + TESNPC::FaceMorphs::PresetCount);
		}

		void SetFacePresets(const std::vector<uint32_t>& pMorphOptions)
		{
			for(uint32_t i = 0; i < pMorphOptions.size(); ++i)
				mData->faceMorph->presets[i] = pMorphOptions[i];
		}
	};

	class BGSLocationHelper : public BaseHelper<BGSLocation>
	{
	public:

		BGSLocationHelper(BGSLocation* ptr) : BaseHelper<BGSLocation>(ptr){};

		std::string GetName()
		{			
			if(mData && mData->fullName.name.data)
				return mData->fullName.name.data;
			return "";
		}
	};
}