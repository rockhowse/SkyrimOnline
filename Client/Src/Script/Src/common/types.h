/*
	THIS FILE IS A PART OF THE SKYRIM DRAGON SCRIPT PROJECT	
				(C) Alexander Blade 2011
			http://Alexander.SannyBuilder.com
*/

#pragma once

#include <windows.h>

// ---- Skyrim Online changes 
#include "skse/GameForms.h"
#include "skse/GameReferences.h"
// ---- End

typedef int ScriptNone;
typedef int ScriptAny;
typedef DWORD uint;
typedef char Axis;

class BGSListForm;
typedef Actor CActor;
class TESWordOfPower;
class TESQuest;
class BGSKeyword;
class BGSLocation;
class BGSLocationRefType;
class BGSMessage;
class BGSMusicType;
class BGSReferenceEffect;
class BGSScene;
class BGSShaderParticleGeometryData;
class BGSSoundCategory;
class EffectSetting;
class TESEffectShader;
class TESFaction;
class TESGlobal;
class TESImageSpaceModifier;
class TESLevCharacter;
class TESLevItem;
class TESLevSpell;
class TESNPC;
class TESClass;
class TESObjectCELL;
class TESKey;
class BGSVoiceType;
class TESWorldSpace;
class TESRace;
class BGSOutfit;
class BGSEncounterZone;
class BGSImpactDataSet;
class TESTopic;
class BGSPerk;
class TESShout;
class SpellItem;
class TESPackage;
class TESObjectWEAP;
class TESObjectARMO;
class TESIdleForm;
class BGSBaseAlias;
class BGSRefAlias;
class BGSLocAlias;
class ScrollItem;
class ActiveEffect;
class TESWeather;
class TESAmmo;
class TESSound;
class TESTopicInfo;
class BGSAssociationType;
class IngredientItem;
class AlchemyItem;
class EnchantmentItem;
class PlayerCharacter;


class ACTOR
{
    ACTOR();
    ~ACTOR();
};
