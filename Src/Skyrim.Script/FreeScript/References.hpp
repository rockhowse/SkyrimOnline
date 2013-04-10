#pragma once
#pragma unmanaged

#include "Forms.hpp"
#include "ExtraData.hpp"

namespace FreeScript
{
	class TESObjectREFR : public TESForm
	{
	public:

		template <class T>
		struct Vector
		{
			T X,Y,Z;
		};
		
		char pad14to24[0x24 - 0x14];

		TESForm* baseForm;
		Vector<float> rot;
		Vector<float> pos;

		TESObjectCELL	* parentCell;
		uint32_t		  pad;
		FreeScript::BaseExtraList	extraData;
		uint32_t          pad50;
	};

	class Actor : public ::FreeScript::TESObjectREFR
	{
	public:
		virtual ~Actor();

		char	pad54to19c[0x19C - 0x54];
	};

	class PlayerCharacter
	{

	};

	class BGSListForm
	{

	};

	class TESQuest
	{

	};

	class TESWordOfPower
	{

	};

	class BGSKeyword
	{

	};

	class BGSMessage
	{

	};

	class BGSMusicType
	{

	};

	class BGSReferenceEffect
	{

	};

	class BGSScene
	{

	};

	class BGSShaderParticleGeometryData
	{

	};

	class BGSSoundCategory
	{

	};

	class EffectSetting
	{

	};

	class TESEffectShader
	{

	};

	class TESFaction
	{

	};

	class TESImageSpaceModifier
	{

	};

	class TESLevCharacter
	{

	};

	class TESLevItem
	{

	};

	class TESLevSpell
	{

	};

	class TESClass
	{

	};

	class BGSOutfit
	{
	};

	class BGSEncounterZone
	{

	};

	class BGSImpactDataSet
	{

	};

	class TESObjectWEAP
	{

	};

	class TESKey
	{

	};

	class TESAmmo
	{

	};

	class TESPackage
	{

	};

	class BGSVoiceType
	{

	};

	class TESTopic
	{

	};

	class TESSound
	{

	};

	class TESIdleForm
	{

	};

	class BGSPerk
	{

	};

	class BGSAssociationType
	{

	};

	class SpellItem
	{

	};

	class TESShout
	{

	};

	class BGSBaseAlias
	{

	};
	
	class BGSRefAlias
	{

	};

	class BGSLocAlias
	{

	};

	class ActiveEffect
	{

	};

	class AlchemyItem
	{

	};

	class EnchantmentItem
	{

	};

	class IngredientItem
	{

	};

	class ScrollItem
	{

	};

	class TESObjectARMO
	{

	};

	class TESWorldSpace
	{

	};
}