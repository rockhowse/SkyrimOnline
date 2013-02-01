#include "stdafx.h"
#include "Character.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLocationId()
		{
			return mRegion;
		}
		//--------------------------------------------------------------------------------
		const std::string& Character::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
		Vector3 Character::GetPosition()
		{
			return mPosition;
		}
		//--------------------------------------------------------------------------------
		Vector3 Character::GetRotation()
		{
			return mRotation;
		}
		//--------------------------------------------------------------------------------
		float Character::GetHeading()
		{
			return mRotation.y;
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
		//--------------------------------------------------------------------------------
		void Character::SetPosition(float x, float y, float z)
		{
			mPosition.x = x;
			mPosition.y = y;
			mPosition.z = z;
		}
		//--------------------------------------------------------------------------------
		void Character::SetRotation(float x, float y, float z)
		{
			mRotation.x = x;
			mRotation.y = y;
			mRotation.z = z;
		}
		//--------------------------------------------------------------------------------
		void Character::SetHeading(float heading)
		{
			mRotation.y = heading;
		}
		//--------------------------------------------------------------------------------
		void Character::SetName(const std::string& pName)
		{
			mName = pName;
		}
		//--------------------------------------------------------------------------------
	}
}