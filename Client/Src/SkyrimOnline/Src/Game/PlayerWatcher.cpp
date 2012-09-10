#include "stdafx.h"
#include <Game/PlayerWatcher.h>
#include <SkyrimOnline.h>
#include <Game/ActorController.h>

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		PlayerWatcher::PlayerWatcher()
			:mPlayer(::Game::GetPlayer()), mMount(false), mEntered(false)
		{
			mRegion = mPlayer.GetLocationId();
		}
		//--------------------------------------------------------------------------------
		void PlayerWatcher::Update(uint32_t elapsed)
		{
			mTimer += elapsed;

			// 4 times per sec update pos and rot
			if(mTimer >= 250)
			{
				mPlayer.SetActor(::Game::GetPlayer());
				// On enter the world
				if(!mEntered)
				{
					mEntered = true;
					OnEnterWorld(mPlayer);
				}

				OnMove(mPlayer, mTimer);

				// if mount or unmount
				if(mMount != mPlayer.IsRidding())
				{
					mMount = mPlayer.IsRidding();
					if(mMount)
					{
						OnMount(mPlayer.GetMountId());
					}
					else
					{
						OnUnmount();
					}
				}
				if(mRegion != mPlayer.GetLocationId() && mPlayer.GetLocationId() != 0)
				{
					mRegion = mPlayer.GetLocationId();
					OnRegion(mRegion);
				}

				mTimer = 0;
			}
		}
		//--------------------------------------------------------------------------------
		bool PlayerWatcher::IsDead()
		{
			return mPlayer.IsDead();
		}
		//--------------------------------------------------------------------------------
		FreeScript::Character& PlayerWatcher::GetCharacter()
		{
			return mPlayer;
		}
		//--------------------------------------------------------------------------------
	}
}