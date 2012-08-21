#pragma once

namespace Skyrim
{
	namespace Game
	{
		class Character
		{
		public:

			Character(CActor* pActor);

			// CActor position
			float GetPosX();
			float GetPosY();
			float GetPosZ();

			float GetRotX();
			float GetRotY();
			float GetRotZ();

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

			const std::vector<float>&		GetFaceMorph();
			void							SetFaceMorph(const std::vector<float>& pFaceMorph);

			TESForm*						GetWornForm(uint32_t mask);
			const std::vector<uint32_t>&	GetAllWornForms();
			void							EquipItems(std::vector<uint32_t> wornForms);

			// Actor info
			BGSLocation* GetLocation();
			uint32_t	 GetLocationId();
			std::string	 GetLocationString();
			void		 SetName(const std::string& pName);

			uint32_t GetCarryWeight();
			uint32_t GetMood();
			uint32_t GetAssistance();
			uint32_t GetEnergy();
			uint32_t GetMorality();
			uint32_t GetOneHanded();
			uint32_t GetTwoHanded();
			uint32_t GetMarksman();
			uint32_t GetBlock();
			uint32_t GetSmithing();
			uint32_t GetHeavyArmor();
			uint32_t GetLightArmor();
			uint32_t GetPickpocket();
			uint32_t GetLockpicking();
			uint32_t GetSneak();
			uint32_t GetAlchemy();
			uint32_t GetSpeechcraft();
			uint32_t GetAlteration();
			uint32_t GetConjuration();
			uint32_t GetDestruction();
			uint32_t GetIllusion();
			uint32_t GetRestoration();
			uint32_t GetEnchanting();
			uint32_t GetHealth();
			uint32_t GetMagicka();
			uint32_t GetStamina();
			uint32_t GetHealRate();
			uint32_t GetMagickaRate();
			uint32_t GetStaminaRate();
			uint32_t GetSpeedMult();
			uint32_t GetInventoryWeight();
			uint32_t GetDragonRend();
			uint32_t GetCritChance();
			uint32_t GetMeleeDamage();
			uint32_t GetUnarmedDamage();
			uint32_t GetMass();
			uint32_t GetVoicePoints();
			uint32_t GetVoiceRate();
			uint32_t GetDamageResist();
			uint32_t GetPoisonResist();
			uint32_t GetFireResist();
			uint32_t GetElectricResist();
			uint32_t GetFrostResist();
			uint32_t GetMagicResist();
			uint32_t GetDiseaseResist();
			uint32_t GetParalysis();
			uint32_t GetInvisibility();
			uint32_t GetNightEye();
			uint32_t GetDetectLifeRange();
			uint32_t GetWaterBreathing();
			uint32_t GetWaterWalking();
			uint32_t GetIgnoreCrippledLimbs();
			uint32_t GetFame();
			uint32_t GetInfamy();
			uint32_t GetJumpingBonus();
			uint32_t GetWardPower();
			uint32_t GetRightItemCharge();
			uint32_t GetLeftItemCharge();
			uint32_t GetEquippedItemCharge();
			uint32_t GetArmorPerks();
			uint32_t GetShieldPerks();
			uint32_t GetFavorActive();
			uint32_t GetFavorsPerDay();
			uint32_t GetFavorsPerDayTimer();
			uint32_t GetEquippedStaffCharge();
			uint32_t GetAbsorbChance();
			uint32_t GetBlindness();
			uint32_t GetWeaponSpeedMult();
			uint32_t GetShoutRecoveryMult();
			uint32_t GetBowStaggerBonus();
			uint32_t GetTelekinesis();
			uint32_t GetFavorPointsBonus();
			uint32_t GetLastBribedIntimidated();
			uint32_t GetLastFlattered();
			uint32_t GetMovementNoiseMult();
			uint32_t GetBypassVendorStolenCheck();
			uint32_t GetBypassVendorKeywordCheck();
			uint32_t GetWaitingForPlayer();
			uint32_t GetOneHandedMod();
			uint32_t GetTwoHandedMod();
			uint32_t GetMarksmanMod();
			uint32_t GetBlockMod();
			uint32_t GetSmithingMod();
			uint32_t GetHeavyArmorMod();
			uint32_t GetLightArmorMod();
			uint32_t GetPickPocketMod();
			uint32_t GetLockpickingMod();
			uint32_t GetSneakMod();
			uint32_t GetAlchemyMod();
			uint32_t GetSpeechcraftMod();
			uint32_t GetAlterationMod();
			uint32_t GetConjurationMod();
			uint32_t GetDestructionMod();
			uint32_t GetIllusionMod();
			uint32_t GetRestorationMod();
			uint32_t GetEnchantingMod();
			uint32_t GetOneHandedSkillAdvance();
			uint32_t GetTwoHandedSkillAdvance();
			uint32_t GetMarksmanSkillAdvance();
			uint32_t GetBlockSkillAdvance();
			uint32_t GetSmithingSkillAdvance();
			uint32_t GetHeavyArmorSkillAdvance();
			uint32_t GetLightArmorSkillAdvance();
			uint32_t GetPickPocketSkillAdvance();
			uint32_t GetLockpickingSkillAdvance();
			uint32_t GetSneakSkillAdvance();
			uint32_t GetAlchemySkillAdvance();
			uint32_t GetSpeechcraftSkillAdvance();
			uint32_t GetAlterationSkillAdvance();
			uint32_t GetConjurationSkillAdvance();
			uint32_t GetDestructionSkillAdvance();
			uint32_t GetIllusionSkillAdvance();
			uint32_t GetRestorationSkillAdvance();
			uint32_t GetEnchantingSkillAdvance();
			uint32_t GetLeftWeaponSpeedMult();
			uint32_t GetDragonSouls();
			uint32_t GetCombatHealthRegenMult();
			uint32_t GetOneHandedPowerMod();
			uint32_t GetTwoHandedPowerMod();
			uint32_t GetMarksmanPowerMod();
			uint32_t GetBlockPowerMod();
			uint32_t GetSmithingPowerMod();
			uint32_t GetHeavyArmorPowerMod();
			uint32_t GetLightArmorPowerMod();
			uint32_t GetPickPocketPowerMod();
			uint32_t GetLockpickingPowerMod();
			uint32_t GetSneakPowerMod();
			uint32_t GetAlchemyPowerMod();
			uint32_t GetSpeechcraftPowerMod();
			uint32_t GetAlterationPowerMod();
			uint32_t GetConjurationPowerMod();
			uint32_t GetDestructionPowerMod();
			uint32_t GetIllusionPowerMod();
			uint32_t GetRestorationPowerMod();
			uint32_t GetEnchantingPowerMod();
			uint32_t GetAttackDamageMult();
			uint32_t GetHealRateMult();
			uint32_t GetMagickaRateMult();
			uint32_t GetStaminaRateMult();
			uint32_t GetCombatHealthRegenMultMod();
			uint32_t GetCombatHealthRegenMultPowerMod();
			uint32_t GetHealRatePowerMod();
			uint32_t GetMagickaRateMod();
			uint32_t GetReflectDamage();
			uint32_t GetNormalWeaponsResist();
			uint32_t GetPerceptionCondition();
			uint32_t GetEnduranceCondition();
			uint32_t GetLeftAttackCondition();
			uint32_t GetRightAttackCondition();
			uint32_t GetLeftMobilityCondition();
			uint32_t GetRightMobilityCondition();
			uint32_t GetBrainCondition();

			bool IsDead();

			CActor* GetActor();
			void SetActor(CActor* pActor);

		private:

			CActor* mActor;
			std::vector<float>    mFaceMorph;
			std::vector<uint32_t> mWornForms;
		};
	}
}