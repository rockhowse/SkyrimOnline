#pragma once

#include "References.hpp"
#include "Forms.hpp"
#include "Actor.hpp"
#include <Math/Vector3.hpp>

using namespace Framework::Math;

namespace FreeScript
{
	class Character
	{
	public:

		Character(FreeScript::Actor* pActor);

		float GetPosX();
		float GetPosY();
		float GetPosZ();
		Vector3 GetPosition();

		float GetRotX();
		float GetRotY();
		float GetRotZ();
		Vector3 GetRotation();

		void SetPos(float x, float y, float z);
		void SetRot(float x, float y, float z);

		void QueueNiNodeUpdate();

		// Mount
		bool IsRidding();
		uint32_t GetMountId();

		// Appearance
		uint32_t GetGender();
		uint32_t GetRace();
		uint32_t GetLevel();

		void SetLevel(uint32_t level);

		const std::vector<float>&		GetFaceMorph();
		void							SetFaceMorph(const std::vector<float>& pFaceMorph);
		const std::vector<uint32_t>&	GetFacePresets();
		void							SetFacePresets(const std::vector<uint32_t>& pFacePresets);

		TESForm*						GetWornForm(uint32_t mask);
		const std::vector<uint32_t>&	GetAllWornForms();
		void							EquipItems(std::vector<uint32_t> wornForms);

		// Actor info
		BGSLocation* GetLocation();
		uint32_t	 GetLocationId();
		std::string	 GetLocationString();
		void		 SetName(const std::string& pName);

		float GetCarryWeight();
		float GetMood();
		float GetAssistance();
		float GetEnergy();
		float GetMorality();
		float GetOneHanded();
		float GetTwoHanded();
		float GetMarksman();
		float GetBlock();
		float GetSmithing();
		float GetHeavyArmor();
		float GetLightArmor();
		float GetPickpocket();
		float GetLockpicking();
		float GetSneak();
		float GetAlchemy();
		float GetSpeechcraft();
		float GetAlteration();
		float GetConjuration();
		float GetDestruction();
		float GetIllusion();
		float GetRestoration();
		float GetEnchanting();
		float GetHealth();
		float GetMagicka();
		float GetStamina();
		float GetHealRate();
		float GetMagickaRate();
		float GetStaminaRate();
		float GetSpeedMult();
		float GetInventoryWeight();
		float GetDragonRend();
		float GetCritChance();
		float GetMeleeDamage();
		float GetUnarmedDamage();
		float GetMass();
		float GetVoicePoints();
		float GetVoiceRate();
		float GetDamageResist();
		float GetPoisonResist();
		float GetFireResist();
		float GetElectricResist();
		float GetFrostResist();
		float GetMagicResist();
		float GetDiseaseResist();
		float GetParalysis();
		float GetInvisibility();
		float GetNightEye();
		float GetDetectLifeRange();
		float GetWaterBreathing();
		float GetWaterWalking();
		float GetIgnoreCrippledLimbs();
		float GetFame();
		float GetInfamy();
		float GetJumpingBonus();
		float GetWardPower();
		float GetRightItemCharge();
		float GetLeftItemCharge();
		float GetEquippedItemCharge();
		float GetArmorPerks();
		float GetShieldPerks();
		float GetFavorActive();
		float GetFavorsPerDay();
		float GetFavorsPerDayTimer();
		float GetEquippedStaffCharge();
		float GetAbsorbChance();
		float GetBlindness();
		float GetWeaponSpeedMult();
		float GetShoutRecoveryMult();
		float GetBowStaggerBonus();
		float GetTelekinesis();
		float GetFavorPointsBonus();
		float GetLastBribedIntimidated();
		float GetLastFlattered();
		float GetMovementNoiseMult();
		float GetBypassVendorStolenCheck();
		float GetBypassVendorKeywordCheck();
		float GetWaitingForPlayer();
		float GetOneHandedMod();
		float GetTwoHandedMod();
		float GetMarksmanMod();
		float GetBlockMod();
		float GetSmithingMod();
		float GetHeavyArmorMod();
		float GetLightArmorMod();
		float GetPickPocketMod();
		float GetLockpickingMod();
		float GetSneakMod();
		float GetAlchemyMod();
		float GetSpeechcraftMod();
		float GetAlterationMod();
		float GetConjurationMod();
		float GetDestructionMod();
		float GetIllusionMod();
		float GetRestorationMod();
		float GetEnchantingMod();
		float GetOneHandedSkillAdvance();
		float GetTwoHandedSkillAdvance();
		float GetMarksmanSkillAdvance();
		float GetBlockSkillAdvance();
		float GetSmithingSkillAdvance();
		float GetHeavyArmorSkillAdvance();
		float GetLightArmorSkillAdvance();
		float GetPickPocketSkillAdvance();
		float GetLockpickingSkillAdvance();
		float GetSneakSkillAdvance();
		float GetAlchemySkillAdvance();
		float GetSpeechcraftSkillAdvance();
		float GetAlterationSkillAdvance();
		float GetConjurationSkillAdvance();
		float GetDestructionSkillAdvance();
		float GetIllusionSkillAdvance();
		float GetRestorationSkillAdvance();
		float GetEnchantingSkillAdvance();
		float GetLeftWeaponSpeedMult();
		float GetDragonSouls();
		float GetCombatHealthRegenMult();
		float GetOneHandedPowerMod();
		float GetTwoHandedPowerMod();
		float GetMarksmanPowerMod();
		float GetBlockPowerMod();
		float GetSmithingPowerMod();
		float GetHeavyArmorPowerMod();
		float GetLightArmorPowerMod();
		float GetPickPocketPowerMod();
		float GetLockpickingPowerMod();
		float GetSneakPowerMod();
		float GetAlchemyPowerMod();
		float GetSpeechcraftPowerMod();
		float GetAlterationPowerMod();
		float GetConjurationPowerMod();
		float GetDestructionPowerMod();
		float GetIllusionPowerMod();
		float GetRestorationPowerMod();
		float GetEnchantingPowerMod();
		float GetAttackDamageMult();
		float GetHealRateMult();
		float GetMagickaRateMult();
		float GetStaminaRateMult();
		float GetCombatHealthRegenMultMod();
		float GetCombatHealthRegenMultPowerMod();
		float GetHealRatePowerMod();
		float GetMagickaRateMod();
		float GetReflectDamage();
		float GetNormalWeaponsResist();
		float GetPerceptionCondition();
		float GetEnduranceCondition();
		float GetLeftAttackCondition();
		float GetRightAttackCondition();
		float GetLeftMobilityCondition();
		float GetRightMobilityCondition();
		float GetBrainCondition();

		bool IsDead();

		Actor* GetActor();
		void SetActor(Actor* pActor);

	private:

		FreeScript::Actor*					mActor;
		std::vector<float>		mFaceMorph;
		std::vector<uint32_t>	mFacePresets;
		std::vector<uint32_t>	mWornForms;
	};



}