#pragma once

#include "Actor.hpp"
#include "References.hpp"
#include "RTTI.hpp"
#include "VM.hpp"

enum 
{
	kStaticFunctionTag = 0
};

template <class T>
struct PapyrusFunction{};

template <class Ret, class... Args>
struct PapyrusFunction<Ret(Args...)>
{
	typedef Ret(*FuncPtr)(VMClassRegistry*,int,Args...);

	static Ret Call(void* addr, Args... args)
	{
		int b = 0; 
		return (*(FuncPtr)addr)(SkyrimVM::GetInstance()->registry,b,args...);
	}
};

template <class... Args>
struct PapyrusFunction<void(Args...)>
{
	typedef void(*FuncPtr)(VMClassRegistry*,int,Args...);

	static void Call(void* addr, Args... args)
	{
		int b = 0; // a probably is the context and b someflag
		(*(FuncPtr)addr)(SkyrimVM::GetInstance()->registry,b,args...);
	}
};

template <class T>
struct StaticPapyrusFunction{};

template <class Ret, class... Args>
struct StaticPapyrusFunction<Ret(Args...)>
{
	typedef Ret(*FuncPtr)(VMClassRegistry*,int, int, Args...);

	static Ret Call(void* addr, Args... args)
	{
		int b = 0; // a probably is the stack and b the stack size
		return (*(FuncPtr)addr)(SkyrimVM::GetInstance()->registry,b, kStaticFunctionTag, args...);
	}
};

template <class... Args>
struct StaticPapyrusFunction<void(Args...)>
{
	typedef void(*FuncPtr)(VMClassRegistry*, int, int, Args...);

	static void Call(void* addr, Args... args)
	{
		int b = 0; // a probably is the context and b someflag
		(*(FuncPtr)addr)(SkyrimVM::GetInstance()->registry, b, kStaticFunctionTag, args...);
	}
};


namespace FreeScript
{
	namespace Debug
	{
		void MessageBOX(const char* str);
		void Notification(const char* str);
	}

	namespace Game
	{

		void DisablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking,
			bool abMenu, bool abActivate, bool abJournalTabs, uint32_t aiDisablePOVType);

		void EnablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking,
			bool abMenu, bool abActivate, bool abJournalTabs, uint32_t aiDisablePOVType);

		TESForm* GetForm(uint32_t id);

		Actor* GetPlayer();

		Actor* GetPlayersLastRiddenHorse();
		void SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);
	}

	namespace ObjectReference
	{
		extern bool (*AddItem)(TESObjectREFR* self, TESForm* form, uint32_t count, bool silent);
		void Delete(TESObjectREFR * self);
		void Disable(TESObjectREFR * self, bool fade);
		void Enable(TESObjectREFR * self, bool abFadeIn);
		BGSLocation* GetCurrentLocation(TESObjectREFR * self);
		float GetDistance(TESObjectREFR* a, TESObjectREFR* b);
		TESObjectREFR* PlaceAtMe(TESObjectREFR* self, TESForm* formToPlace, int count = 1, bool forcePersist = false, bool disabled = false);
		void SetAngle(TESObjectREFR * self, float x, float y, float z);
		void SetPosition(TESObjectREFR * self, float afX, float afY, float afZ);
		void SetScale(TESObjectREFR * self, float scale);
	}

	namespace NPC
	{
		int GetSex(TESNPC* npc);
	}

	namespace SActor
	{
		void Dismount(Actor* actor);
		void DrawWeapon(Actor* actor);
		void EnableAI(Actor* actor, bool enabled);
		void EquipItem(Actor* actor, TESForm* form, bool preventRemoval, bool silent);
		void ForceActorValue(Actor* actor, const char* name, float val);
		float GetActorValue(Actor* actor, const char* name);
		float GetBaseActorValue(Actor* actor, const char* name);
		int GetLevel(Actor* actor);
		bool IsDead(Actor* actor);
		bool IsOnMount(Actor* actor);

		void KeepOffsetFromActor(Actor* self, Actor* arTarget, float afOffsetX, float afOffsetY, float afOffsetZ, float afOffsetAngleX = 0.0,
			float afOffsetAngleY = 0.0,  float afOffsetAngleZ = 0.0, float afCatchUpRadius = 20.0, float afFollowRadius = 5.0);

		char Resurrect(Actor* actor);
		void SetActorValue(Actor* actor, const char* name, float val);
		void UnequipAll(Actor* actor);

	}

	namespace Weather
	{
		void ForceActive(TESWeather* self, bool Override);
		TESWeather* GetCurrentWeather();
	}

	namespace GlobalVariable
	{
		float GetValue(TESGlobal * self);
		void SetValue(TESGlobal * self, float afNewValue);
	}


	inline bool GetGlobalSetting(int formIDSetting, float *fSetting)
	{
		TESGlobal *pGlobalSetting = rtti_cast(Game::GetForm(formIDSetting), TESForm, TESGlobal);
		if (!pGlobalSetting)
			return false;
		*fSetting = GlobalVariable::GetValue(pGlobalSetting);
		return true;
	}

	inline bool SetGlobalSetting(int formIDSetting, float fSetting)
	{
		TESGlobal *pGlobalSetting = rtti_cast(Game::GetForm(formIDSetting), TESForm, TESGlobal);
		if (!pGlobalSetting)
			return false;
		GlobalVariable::SetValue(pGlobalSetting,fSetting);
		return true;
	}
}