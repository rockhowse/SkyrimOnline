#include "stdafx.h"
#include "CharacterManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		CharacterManager::CharacterManager()
		{
		}
		//--------------------------------------------------------------------------------
		CharacterManager::~CharacterManager()
		{
			System::Log::Debug("CharacterManager::~CharacterManager()");
			for(auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
			{
				delete itor->second;
			}
			mCharacters.clear();
		}
		//--------------------------------------------------------------------------------
		void CharacterManager::Add(RemotePlayer* pPlayer)
		{
			if(mCharacters.find(pPlayer->GetId()) == mCharacters.end())
				mCharacters[pPlayer->GetId()] = pPlayer;
		}
		//--------------------------------------------------------------------------------
		RemotePlayer* CharacterManager::Remove(RemotePlayer* pPlayer)
		{
			auto itor = mCharacters.find(pPlayer->GetId());
			if(itor != mCharacters.end())
				mCharacters.erase(itor);
			return pPlayer;
		}
		//--------------------------------------------------------------------------------
		RemotePlayer* CharacterManager::Get(uint32_t pPlayer)
		{
			auto itor = mCharacters.find(pPlayer);
			if(itor != mCharacters.end())
				return itor->second;
			return nullptr;
		}
		//--------------------------------------------------------------------------------
		void CharacterManager::Update(uint32_t elapsed)
		{
			for(auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
			{
				itor->second->Update(elapsed);
			}
		}
		//--------------------------------------------------------------------------------
	}
}