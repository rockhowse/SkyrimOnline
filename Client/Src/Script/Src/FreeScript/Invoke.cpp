#include "stdafx.h"

#include "Invoke.hpp"


namespace FreeScript
{
	namespace Debug
	{
		void* fMessageBox = (void*)0x8ee530;
		void* fNotification = (void*)0x8ee550;

		void MessageBOX(const char* str)
		{
			BSString bstr(str);
			StaticPapyrusFunction<void(BSString*)>::Call(fMessageBox, &bstr);
		}

		void Notification(const char* str)
		{
			BSString bstr(str);
			StaticPapyrusFunction<void(BSString*)>::Call(fNotification, &bstr);
		}
	}

	namespace Game
	{
		void* fDisablePlayerControls = (void*)0x8f2ff0;
		void* fEnablePlayerControls = (void*)0x8f30a0;
		void* fGetForm = (void*)0x8f0c10;
		void* fGetPlayer = (void*)0x8f0f40;
		void* fGetPlayersLastRiddenHorse = (void*)0x8f4740;
		void* fSetInChargen = (void*)0x8f1200;

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

		void SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage)
		{
			StaticPapyrusFunction<void(bool,bool,bool)>::Call(fSetInChargen, abDisableSaving, abDisableWaiting, abShowControlsDisabledMessage);
		}
	}

	namespace ObjectReference
	{
		void* fAddItem = (void*)0x908120;
		void* fDelete = (void*)0x9084a0;
		void* fDisable = (void*)0x908790;
		void* fEnable = (void*)0x908ac0;
		void* fGetCurrentLocation = (void*)0x902d30;
		void* fGetDistance = (void*)0x9026e0;
		void* fPlaceAtMe = (void*)0x90d1d0;
		void* fSetAngle = (void*)0x909880;
		void* fSetScale = (void*)0x90a210;
		void* fSetPosition = (void*)0x909e40;
		
		/*bool AddItem(TESObjectREFR* self, TESForm* form, uint32_t count, bool silent)
		{
			return PapyrusFunction<bool(TESObjectREFR*, TESForm*, uint32_t, bool)>::Call(fAddItem, self, form, count, silent);
		}*/

		// For now point this to Papyrus as it's a latent function...
		bool (*AddItem)(TESObjectREFR* self, TESForm* form, uint32_t count, bool silent) = 0;

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

		float GetDistance(TESObjectREFR* a, TESObjectREFR* b)
		{
			return PapyrusFunction<float(TESObjectREFR*, TESObjectREFR*)>::Call(fGetDistance, a, b);
		}

		TESObjectREFR* PlaceAtMe(TESObjectREFR* me, TESForm* formToPlace, int count, bool forcePersist, bool disabled)
		{
			return PapyrusFunction<TESObjectREFR*(TESObjectREFR*, TESForm*, int, bool, bool)>::
				Call(fPlaceAtMe, me, formToPlace, count, forcePersist, disabled);
		}

		void SetAngle(TESObjectREFR * self, float x, float y, float z)
		{
			PapyrusFunction<void(TESObjectREFR*,float, float, float)>::Call(fSetAngle, self, x, y ,z);
		}

		void SetScale(TESObjectREFR * self, float scale)
		{
			PapyrusFunction<void(TESObjectREFR*,float)>::Call(fSetScale, self, scale);
		}

		void SetPosition(TESObjectREFR * self, float afX, float afY, float afZ)
		{
			PapyrusFunction<void(TESObjectREFR*,float,float,float)>::Call(fSetPosition, self, afX, afY, afZ);
		}		
	}

	namespace NPC
	{
		void* fGetSex = (void*)0x8ffb80;

		int GetSex(TESNPC* npc)
		{
			if(npc)
				PapyrusFunction<int(TESNPC*)>::Call(fGetSex, npc);
			return 0;
		}
	}

	namespace SActor
	{
		void* fDismount = (void*)0x8daea0;
		void* fDrawWeapon = (void*)0x8da5a0; //TODO
		void* fEnableAI = (void*)0x8daee0;
		void* fEquipItem = (void*)0x8dd460;
		void* fForceActorValue = (void*)0x8dd5a0;
		void* fGetActorValue = (void*)0x8db430;
		void* fGetBaseActorValue = (void*)0x8da720;
		void* fGetLevel = (void*)0x8daf60;
		void* fIsDead = (void*)0x8da830;
		void* fIsOnMount = (void*)0x8dcb40;
		void* fKeepOffsetFromActor = (void*)0x8da850;
		void* fResurrect = (void*)0x8dd990;
		void* fSetActorValue = (void*)0x8e1490;
		void* fUnequipAll = (void*)0x8ddef0;
		
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

		void KeepOffsetFromActor(Actor* self, Actor* arTarget, float afOffsetX, float afOffsetY, float afOffsetZ, float afOffsetAngleX /* = 0.0 */, float afOffsetAngleY /* = 0.0 */, float afOffsetAngleZ /* = 0.0 */, float afCatchUpRadius /* = 20.0 */, float afFollowRadius /* = 5.0 */)
		{
			if(arTarget)
				PapyrusFunction<void(Actor*,Actor*,float,float,float,float,float,float,float,float)>::
					Call(fKeepOffsetFromActor, self, arTarget, afOffsetX, afOffsetY, afOffsetZ, afOffsetAngleX, afOffsetAngleY, afOffsetAngleZ, afCatchUpRadius, afFollowRadius);
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
		void* fForceActive = (void*)0x917fe0;
		void* fGetCurrentWeather = (void*)0x918090;

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
		void* fGetValue = (void*)0x8fe2a0;
		void* fSetValue = (void*)0x8fe2b0;

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

