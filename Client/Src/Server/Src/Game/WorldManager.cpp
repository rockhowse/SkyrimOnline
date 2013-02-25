#include "stdafx.h"
#include "WorldManager.h"
#include "Object.hpp"
#include "Character.hpp"
#include "NPC.hpp"
#include "Area.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WorldManager::WorldManager()
		{
			WeatherManager::Register(&mScript);
			mTime.Register(&mScript);

			Object::Register(&mScript);
			Character::Register(&mScript);
			NPC::Register(&mScript);
			Area::Register(&mScript);
			Register();

			NPC npc;
			mScript.ReloadScripts();
			
			mScript.FireEvent("test 2", "void OnNew(NPC@)", &npc);
			mScript.FireEvent("test 2", "void OnDeath(NPC@)", &npc);
		}
		//--------------------------------------------------------------------------------
		WorldManager::~WorldManager()
		{
		}
		//--------------------------------------------------------------------------------
		void WorldManager::Update(float pDelta)
		{
			mScript.FireEvent("[WORLD]", "void OnUpdate(float)", pDelta);
		}
		//--------------------------------------------------------------------------------
		void WorldManager::Register()
		{
			mScript.RegisterReferenceClass(WorldManager);
			mScript.RegisterGlobal("WorldManager World", this);
			mScript.RegisterMethod(WorldManager, "Area@ GetArea(string &in)", GetArea);
		}
		//--------------------------------------------------------------------------------
		Area* WorldManager::GetArea(const std::string& pArea)
		{
			return &mAreas[pArea];
		}
		//--------------------------------------------------------------------------------
		WorldState WorldManager::GetWorldState(const std::string& pArea)
		{
			WorldState state;
			state.SetWeather(GetArea(pArea)->GetWeather()->GetId());
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