#include "stdafx.h"
#include "ControllerManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		ControllerManager::ControllerManager()
		{
		}
		//--------------------------------------------------------------------------------
		ControllerManager::~ControllerManager()
		{
			_trace
			for(auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
			{
				delete itor->second;
			}
			mCharacters.clear();
		}
		//--------------------------------------------------------------------------------
		void ControllerManager::Add(ActorController* pPlayer)
		{
			if(mCharacters.find(pPlayer->GetId()) == mCharacters.end())
				mCharacters[pPlayer->GetId()] = pPlayer;
		}
		//--------------------------------------------------------------------------------
		ActorController* ControllerManager::Remove(ActorController* pPlayer)
		{
			auto itor = mCharacters.find(pPlayer->GetId());
			if(itor != mCharacters.end())
				mCharacters.erase(itor);
			return pPlayer;
		}
		//--------------------------------------------------------------------------------
		ActorController* ControllerManager::Get(uint32_t pPlayer)
		{
			auto itor = mCharacters.find(pPlayer);
			if(itor != mCharacters.end())
				return itor->second;
			return nullptr;
		}
		//--------------------------------------------------------------------------------
	}
}