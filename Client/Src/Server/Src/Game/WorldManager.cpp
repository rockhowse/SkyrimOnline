#include "stdafx.h"
#include "WorldManager.h"
#include "Object.hpp"
#include "Character.hpp"
#include "NPC.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WorldManager::WorldManager()
		{
			mWeather.Register(&mScript);
			mTime.Register(&mScript);

			Object::Register(&mScript);
			Character::Register(&mScript);
			NPC::Register(&mScript);

			NPC npc;
			mScript.ReloadScripts();
			
			//mScript.FireEvent("test 2", "void OnDeath(string)", string("test 2"));
			mScript.FireEvent("test 2", "void OnNew(NPC@)", &npc);
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
		void WorldManager::SendWorldStateUpdate(WorldState& state)
		{
			TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerSynchronized, state.ToPacket(kServerWorldState));
		}
		//--------------------------------------------------------------------------------
	}
}