#include "stdafx.h"
#include "WorldManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WorldManager::WorldManager()
		{
		}
		//--------------------------------------------------------------------------------
		WorldManager::~WorldManager()
		{
		}
		//--------------------------------------------------------------------------------
		void WorldManager::Update(float pDelta)
		{
			mWeather.Update(pDelta);
		}
		//--------------------------------------------------------------------------------
		WorldState WorldManager::GetWorldState()
		{
			WorldState state;
			state.SetWeather(mWeather.GetWeatherForArea(0));
			return std::move(state);
		}
		//--------------------------------------------------------------------------------
	}
}