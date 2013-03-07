#include "stdafx.h"

#include "Invoke.hpp"


namespace FreeScript
{
	namespace Game
	{
		void* fDisablePlayerControls = (void*)0x8f22a0;
		void* fEnablePlayerControls = (void*)0x8f2350;
		void* fGetForm = (void*)0x8EFEB0;
		void* fGetPlayer = (void*)0x8f01f0;
		void* fGetPlayersLastRiddenHorse = (void*)0x8f3a40;

		void DisablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, uint32_t aiDisablePOVType) {
			StaticPapyrusFunction<void(bool, bool, bool, bool, bool, bool, bool, bool, uint32_t)>::
				Call(fDisablePlayerControls, abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
		}

		void EnablePlayerControls(bool abMovement, bool abFighting, bool abCamSwitch, bool abLooking, bool abSneaking, bool abMenu, bool abActivate, bool abJournalTabs, uint32_t aiDisablePOVType) {
			StaticPapyrusFunction<void(bool, bool, bool, bool, bool, bool, bool, bool, uint32_t)>::
				Call(fEnablePlayerControls, abMovement, abFighting, abCamSwitch, abLooking, abSneaking, abMenu, abActivate, abJournalTabs, aiDisablePOVType);
		}

		TESForm* GetForm(uint32_t id)
		{
			return StaticPapyrusFunction<TESForm*(uint32_t)>::Call(fGetForm, id);
		}

		Actor* GetPlayer()
		{
			return PapyrusFunction<Actor*()>::Call(fGetPlayer);
		}

		Actor* GetPlayersLastRiddenHorse()
		{
			return PapyrusFunction<Actor*()>::Call(fGetPlayersLastRiddenHorse);
		}
	}

	namespace ObjectReference
	{
		void* fAddItem = (void*)0x9074c0;
		void* fDelete = (void*)0x907840;
		void* fDisable = (void*)0x907b30;
		void* fEnable = (void*)0x907e60;
		void* fGetCurrentLocation = (void*)0x901ff0;
		void* fSetAngle = (void*)0x908c20;
		void* fSetPosition = (void*)0x909230;
		void* fSetScale = (void*)0x909550;

		void AddItem(TESObjectREFR* self, TESForm* form, uint32_t count, bool silent)
		{
			PapyrusFunction<void(TESObjectREFR*, TESForm*, uint32_t, bool)>::Call(fAddItem, self, form, count, silent);
		}

		void Delete(TESObjectREFR * self)
		{
			PapyrusFunction<void(TESObjectREFR*)>::Call(fDelete, self);
		}

		void Disable(TESObjectREFR * self, bool fade)
		{
			PapyrusFunction<void(TESObjectREFR*, bool)>::Call(fDisable, self, fade);
		}

		void Enable(TESObjectREFR * self, bool fade)
		{
			PapyrusFunction<void(TESObjectREFR*, bool)>::Call(fEnable, self, fade);
		}

		BGSLocation* GetCurrentLocation(TESObjectREFR * self)
		{
			return PapyrusFunction<BGSLocation* (TESObjectREFR*)>::Call(fGetCurrentLocation, self);
		}

		void SetAngle(TESObjectREFR * self, float x, float y, float z)
		{
			PapyrusFunction<void(TESObjectREFR*,float, float, float)>::Call(fSetAngle, self, x, y ,z);
		}

		void SetPosition(TESObjectREFR * self, float afX, float afY, float afZ)
		{
			PapyrusFunction<void(TESObjectREFR*,float,float,float)>::Call(fSetPosition, self, afX, afY, afZ);
		}

		void SetScale(TESObjectREFR * self, float scale)
		{
			PapyrusFunction<void(TESObjectREFR*,float)>::Call(fSetScale, self, scale);
		}
	}

	namespace NPC
	{
		void* fGetSex = (void*)0x8fef20;

		int GetSex(TESNPC* npc)
		{
			if(npc)
				PapyrusFunction<int(TESNPC*)>::Call(fGetSex, npc);
			return 0;
		}
	}

	namespace SActor
	{
		void* fDismount = (void*)0x8da600;
		void* fDrawWeapon = (void*)0x8da5a0;
		void* fEnableAI = (void*)0x8da640;
		void* fEquipItem = (void*)0x8dcca0;
		void* fForceActorValue = (void*)0x8dcfa0;
		void* fGetActorValue = (void*)0x8dab90;
		void* fGetBaseActorValue = (void*)0x8d9e80;
		void* fGetLevel = (void*)0x8da6c0;
		void* fIsDead = (void*)0x8d9f90;
		void* fIsOnMount = (void*)0x8dc2a0;
		void* fKeepOffsetFromActor = (void*)0x8d9fb0;
		void* fResurrect = (void*)0x8dd390;
		void* fSetActorValue = (void*)0x8dd560;
		void* fUnequipAll = (void*)0x8dda50;
		
		void Dismount(Actor* actor)
		{
			if(actor)
				PapyrusFunction<void(Actor*)>::Call(fDismount, actor);
		}

		void DrawWeapon(Actor* actor)
		{
			if(actor)
				PapyrusFunction<void(Actor*)>::Call(fDrawWeapon, actor);
		}

		void EnableAI(Actor* actor, bool enabled)
		{
			if(actor)
				PapyrusFunction<void(Actor*, bool)>::Call(fEnableAI, actor, enabled);
		}

		void EquipItem(Actor* actor, TESForm* form, bool preventRemoval, bool silent)
		{
			if(actor)
				PapyrusFunction<void(Actor*, TESForm*, bool, bool)>::Call(fEquipItem, actor, form, preventRemoval, silent);
		}

		void ForceActorValue(Actor* actor, const char* name, float val)
		{
			BSString str(name);
			if(actor)
				PapyrusFunction<void(Actor*, BSString*, float)>::Call(fForceActorValue, actor, &str, val);
		}

		float GetActorValue(Actor* actor, const char* name)
		{
			BSString str(name);
			if(actor)
				return PapyrusFunction<float(Actor*, BSString*)>::Call(fGetActorValue, actor, &str);
			return 0.f;
		}

		float GetBaseActorValue(Actor* actor, const char* name)
		{
			BSString str(name);
			if(actor)
				return PapyrusFunction<float(Actor*, BSString*)>::Call(fGetBaseActorValue, actor, &str);
			return 0.f;
		}

		int GetLevel(Actor* actor)
		{
			if(actor)
				return PapyrusFunction<int(Actor*)>::Call(fGetLevel, actor);
			return -1;
		}

		bool IsDead(Actor* actor)
		{
			if(actor)
				return PapyrusFunction<bool(Actor*)>::Call(fIsDead, actor);
			return false;
		}

		bool IsOnMount(Actor* actor)
		{
			if(actor)
				return PapyrusFunction<bool(Actor*)>::Call(fIsOnMount, actor);
			return false;
		}

		void KeepOffsetFromActor(Actor* arTarget, float afOffsetX, float afOffsetY, float afOffsetZ, float afOffsetAngleX /* = 0.0 */, float afOffsetAngleY /* = 0.0 */, float afOffsetAngleZ /* = 0.0 */, float afCatchUpRadius /* = 20.0 */, float afFollowRadius /* = 5.0 */)
		{
			if(arTarget)
				PapyrusFunction<void(Actor*,float,float,float,float,float,float,float,float)>::
					Call(fKeepOffsetFromActor, arTarget, afOffsetX, afOffsetY, afOffsetZ, afOffsetAngleX, afOffsetAngleY, afOffsetAngleZ, afCatchUpRadius, afFollowRadius);
		}

		char Resurrect(Actor* actor)
		{
			if(actor)
				return PapyrusFunction<char(Actor*)>::Call(fResurrect, actor);
			return 0;
		}

		void SetActorValue(Actor* actor, const char* name, float val)
		{
			BSString str(name);
			if(actor)
				PapyrusFunction<void(Actor*, BSString*, float)>::Call(fSetActorValue, actor, &str, val);
		}

		void UnequipAll(Actor* actor)
		{
			if(actor)
				PapyrusFunction<void(Actor*)>::Call(fUnequipAll, actor);
		}

	}

	namespace Weather
	{
		void* fForceActive = (void*)0x917820;
		void* fGetCurrentWeather = (void*)0x9178d0;

		void ForceActive(TESWeather* self, bool Override)
		{
			if(self)
				PapyrusFunction<void(TESWeather*,bool)>::Call(fForceActive, self, Override);
		}

		TESWeather* GetCurrentWeather()
		{
			return StaticPapyrusFunction<TESWeather*()>::Call(fGetCurrentWeather);
		}
	}

	namespace GlobalVariable
	{
		void* fGetValue = (void*)0x8fd640;
		void* fSetValue = (void*)0x8fd650;

		float GetValue(TESGlobal * self)
		{
			return PapyrusFunction<float(TESGlobal*)>::Call(fGetValue, self);
		}

		void SetValue(TESGlobal * self, float value)
		{
			return PapyrusFunction<void(TESGlobal*, float)>::Call(fGetValue, self, value);
		}
	}
}

