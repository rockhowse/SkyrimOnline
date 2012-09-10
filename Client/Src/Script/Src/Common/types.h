/*
	THIS FILE IS A PART OF THE SKYRIM DRAGON SCRIPT PROJECT	
				(C) Alexander Blade 2011
			http://Alexander.SannyBuilder.com
*/

#pragma once

#include <FreeScript/FreeScript.hpp>
#include <windows.h>

typedef int ScriptNone;
typedef int ScriptAny;
typedef DWORD uint;
typedef char Axis;

using namespace FreeScript;

typedef Actor CActor;

class BGSListForm;
class TESWordOfPower;
class TESQuest;
class BGSKeyword;
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
class TESClass;
class TESKey;
class BGSVoiceType;
class TESWorldSpace;
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

class BaseFormComponent
{
public:
	BaseFormComponent();
	~BaseFormComponent();
	virtual void forcevmt();
};

class TESChildCell
{
	TESChildCell();
	~TESChildCell();
}; 

class BGSListForm
{
	BGSListForm();
	~BGSListForm();
};

class TESWordOfPower
{
	TESWordOfPower();
	~TESWordOfPower();
};

class TESQuest
{
	TESQuest();
	~TESQuest();
};

class BGSKeyword
{
	BGSKeyword();
	~BGSKeyword();
};

class BGSLocationRefType
{
	BGSLocationRefType();
	~BGSLocationRefType();
};

class BGSMessage
{
	BGSMessage();
	~BGSMessage();
};

class BGSMusicType
{
	BGSMusicType();
	~BGSMusicType();
};

class BGSReferenceEffect
{
	BGSReferenceEffect();
	~BGSReferenceEffect();
};

class BGSScene
{
	BGSScene();
	~BGSScene();
};

class BGSShaderParticleGeometryData
{
	BGSShaderParticleGeometryData();
	~BGSShaderParticleGeometryData();
};

class BGSSoundCategory
{
	BGSSoundCategory();
	~BGSSoundCategory();
};

class EffectSetting
{
	EffectSetting();
	~EffectSetting();
};

class TESEffectShader
{
	TESEffectShader();
	~TESEffectShader();
};

class TESFaction
{
	TESFaction();
	~TESFaction();
};

class TESGlobal
{
	TESGlobal();
	~TESGlobal();
};

class TESImageSpaceModifier
{
	TESImageSpaceModifier();
	~TESImageSpaceModifier();
};

class TESLevCharacter
{
	TESLevCharacter();
	~TESLevCharacter();
};

class TESLevItem
{
	TESLevItem();
	~TESLevItem();
};

class TESLevSpell
{
	TESLevSpell();
	~TESLevSpell();
};

class TESClass
{
	TESClass();
	~TESClass();
};

class TESKey
{
	TESKey();
	~TESKey();
};

class BGSVoiceType
{
	BGSVoiceType();
	~BGSVoiceType();
};

class TESWorldSpace
{
	TESWorldSpace();
	~TESWorldSpace();
};

class BGSOutfit
{
	BGSOutfit();
	~BGSOutfit();
};

class BGSEncounterZone
{
	BGSEncounterZone();
	~BGSEncounterZone();
};

class BGSImpactDataSet
{
	BGSImpactDataSet();
	~BGSImpactDataSet();
};

class TESTopic
{
	TESTopic();
	~TESTopic();
};

class BGSPerk
{
	BGSPerk();
	~BGSPerk();
};

class TESShout
{
	TESShout();
	~TESShout();
};

class SpellItem
{
	SpellItem();
	~SpellItem();
};

class TESPackage
{
	TESPackage();
	~TESPackage();
};

class TESObjectWEAP
{
	TESObjectWEAP();
	~TESObjectWEAP();
};

class TESObjectARMO
{
	TESObjectARMO();
	~TESObjectARMO();
};

class TESIdleForm
{
	TESIdleForm();
	~TESIdleForm();
};

class BGSBaseAlias
{
	BGSBaseAlias();
	~BGSBaseAlias();
};

class BGSRefAlias
{
	BGSRefAlias();
	~BGSRefAlias();
};

class BGSLocAlias
{
	BGSLocAlias();
	~BGSLocAlias();
};

class ScrollItem
{
	ScrollItem();
	~ScrollItem();
};

class ActiveEffect
{
	ActiveEffect();
	~ActiveEffect();
};

class TESWeather
{
	TESWeather();
	~TESWeather();
};

class TESAmmo
{
	TESAmmo();
	~TESAmmo();
};

class TESSound
{
	TESSound();
	~TESSound();
};

class TESTopicInfo
{
	TESTopicInfo();
	~TESTopicInfo();
};

class BGSAssociationType
{
	BGSAssociationType();
	~BGSAssociationType();
};

class IngredientItem
{
	IngredientItem();
	~IngredientItem();
};

class AlchemyItem
{
	AlchemyItem();
	~AlchemyItem();
};

class EnchantmentItem
{
	EnchantmentItem();
	~EnchantmentItem();
};

class PlayerCharacter
{
	PlayerCharacter();
	~PlayerCharacter();
};
