#include "stdafx.h"
#include "Character.hpp"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void Character::Register(ScriptEngine* engine)
		{
			engine->RegisterReferenceClass(Character);
			engine->RegisterInheritance(Object, Character);
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLocationId()
		{
			return mRegion;
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRace()
		{
			return mRace;
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetGender()
		{
			return mGender;
		}
		//--------------------------------------------------------------------------------
		const std::vector<float>& Character::GetFaceMorph()
		{
			return mFaceMorphs;
		}
		//--------------------------------------------------------------------------------
		const std::vector<uint32_t>& Character::GetFacePresets()
		{
			return mPresets;
		}
		//--------------------------------------------------------------------------------
		const std::vector<uint32_t>& Character::GetAllWornForms()
		{
			return mWornForms;
		}
		void Character::SetFaceMorph(const std::vector<float>& faceMorphs)
		{
			mFaceMorphs = faceMorphs;
		}
		//--------------------------------------------------------------------------------
		void Character::SetFacePresets(const std::vector<uint32_t>& facePresets)
		{
			mPresets = facePresets;
		}
		//--------------------------------------------------------------------------------
		void Character::EquipItems(const std::vector<uint32_t>& items)
		{
			mWornForms = items;
		}
		//--------------------------------------------------------------------------------
	}
}