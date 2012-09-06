#include "Forms.hpp"
#include "Common.hpp"

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

		std::string GetDebugName()
		{			
			if(mData)
				return std::to_string((uint64_t)mData->formID) + std::string(" ") + GetName();
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
				mData->faceMorph->option[i] = pMorphOptions.at(i);
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