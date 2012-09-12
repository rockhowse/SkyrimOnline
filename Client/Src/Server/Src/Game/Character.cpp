#include <Game/Character.h>
#include <Game/Mount.h>

namespace Skyrim
{
	namespace Game
	{
		//---------------------------------------------------------------------
		Character::Character()
		{
		}
		//---------------------------------------------------------------------
		Character::~Character()
		{
		}
		//---------------------------------------------------------------------
		unsigned int Character::GetLevel()
		{
			return mLevel;
		}
		//---------------------------------------------------------------------
		unsigned int Character::GetRace()
		{
			return mRace;
		}
		//---------------------------------------------------------------------
		unsigned int Character::GetGender()
		{
			return mGender;
		}
		//---------------------------------------------------------------------
		const std::vector<float>& Character::GetFaceMorph()
		{
			return mFaceMorph;
		}
		//---------------------------------------------------------------------
		const std::vector<uint32_t>& Character::GetWornForms()
		{
			return mWornForms;
		}
		//---------------------------------------------------------------------
		boost::shared_ptr<Mount> Character::GetMount()
		{
			return mMount;
		}
		//---------------------------------------------------------------------
		bool Character::HasMount()
		{
			return mMount != nullptr;
		}
		//---------------------------------------------------------------------
		void Character::SetMount(unsigned int pMountID)
		{
			if(HasMount())
			{
				if(mMount->GetSkyrimId() == pMountID)
					return;
				mMount.reset();
			}
			mMount = boost::make_shared<Mount>(pMountID);
		}
		//---------------------------------------------------------------------
	}
}