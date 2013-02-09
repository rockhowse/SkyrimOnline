#include "stdafx.h"
#include "WorldManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WorldManager::WorldManager()
		{
			mWeather.Register(&mScript);
			mTime.Register(&mScript);

			mScript.ReloadScripts();
			mScript.FireEvent("test 2", "void OnDeath(string)", string("test 2"));
		}
		//--------------------------------------------------------------------------------
		WorldManager::~WorldManager()
		{
		}
		//--------------------------------------------------------------------------------
		void WorldManager::Update(float pDelta)
		{
			mWeather.Update(pDelta);
			mScript.FireEvent("[WORLD]", "void OnUpdate(float)", pDelta);
		}
		//--------------------------------------------------------------------------------
		void WorldManager::Register()
		{
			mScript.RegisterClassType("WorldManager");
		}
		//--------------------------------------------------------------------------------
		WorldState WorldManager::GetWorldState()
		{
			WorldState state;
			state.SetWeather(mWeather.GetWeatherForArea(0));
			return std::move(state);
		}
		//--------------------------------------------------------------------------------
		ScriptEngine& WorldManager::GetScriptEngine()
		{
			return mScript;
		}
		//--------------------------------------------------------------------------------
	}
}