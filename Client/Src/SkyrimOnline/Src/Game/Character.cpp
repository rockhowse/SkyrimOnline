#include "stdafx.h"
#include "Character.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		Character::Character(CActor* pActor)
			:mActor((FreeScript::Actor*)pActor)
		{
			mFaceMorph.reserve(19);
			mWornForms.reserve(32);
		}
		//--------------------------------------------------------------------------------
		bool Character::IsDead()
		{
			return Actor::IsDead((CActor*)mActor);
		}
		//--------------------------------------------------------------------------------
		bool Character::IsRidding()
		{
			return false; //Obscript::IsRidingHorse((TESObjectREFR*)mActor) == 1.f;
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosX()
		{
			return ObjectReference::GetPositionX((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosY()
		{
			return ObjectReference::GetPositionY((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosZ()
		{
			return ObjectReference::GetPositionZ((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotX()
		{
			return ObjectReference::GetAngleX((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotY()
		{
			return ObjectReference::GetAngleY((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotZ()
		{
			return ObjectReference::GetAngleZ((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		void Character::SetPos(float x, float y, float z)
		{
			ObjectReference::SetPosition((TESObjectREFR*)mActor,x,y,z);
		}
		//--------------------------------------------------------------------------------
		void Character::SetRot(float x, float y, float z)
		{
			ObjectReference::SetAngle((TESObjectREFR*)mActor, x,y,z);
		}
		//--------------------------------------------------------------------------------
		void Character::QueueNiNodeUpdate()
		{
			SkyrimScript::QueueNiNodeUpdate(mActor);
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLevel()
		{
			return Actor::GetLevel((CActor*)mActor);
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRace()
		{
			return SkyrimScript::GetRace(mActor);
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetGender()
		{
			return ActorBase::GetSex((TESNPC*)rtti_cast(SkyrimScript::GetBaseForm(mActor), TESForm, TESNPC));
		}
		//--------------------------------------------------------------------------------
		const std::vector<float>& Character::GetFaceMorph()
		{
			SkyrimScript::GetFaceMorph(rtti_cast(SkyrimScript::GetBaseForm(mActor), TESForm, TESNPC), &mFaceMorph);
			return mFaceMorph;
		}
		//--------------------------------------------------------------------------------
		void Character::SetFaceMorph(const std::vector<float>& pFaceMorphs)
		{
			mFaceMorph = pFaceMorphs;
			SkyrimScript::SetFaceMorph(rtti_cast(SkyrimScript::GetBaseForm(mActor), TESForm, TESNPC), &mFaceMorph);
			this->QueueNiNodeUpdate();
		}
		//--------------------------------------------------------------------------------
		void Character::EquipItems(std::vector<uint32_t> wornForms)
		{
			Actor::UnequipAll((CActor*)mActor);
			for( auto itor = wornForms.begin(); itor != wornForms.end(); ++itor )
			{
				if( *itor != 0 )
				{
					ObjectReference::AddItem((TESObjectREFR*)dyn_cast(mActor, "CActor", "TESObjectREFR"), ::Game::GetFormById(*itor), 1, true);
					Actor::EquipItem((CActor*)mActor, ::Game::GetFormById(*itor), true, false); 
				}
			}
		}
		//--------------------------------------------------------------------------------
		TESForm* Character::GetWornForm(uint32_t mask)
		{
			return (TESForm*)SkyrimScript::GetWornForm(mActor,mask);
		}
		//--------------------------------------------------------------------------------
		const std::vector<uint32_t>& Character::GetAllWornForms()
		{
			mWornForms.clear();
			for(uint32_t i=0; i <= 31; i++)
			{
				TESForm* pForm = this->GetWornForm(i);
				if( pForm != nullptr )
				{
					mWornForms.push_back(pForm->ref_id);
				}
				else
				{
					mWornForms.push_back(0);
				}
			}
			return mWornForms;
		}
		//--------------------------------------------------------------------------------
		BGSLocation* Character::GetLocation()
		{
			try{
				return ObjectReference::GetCurrentLocation((TESObjectREFR*)dyn_cast(mActor, "CActor", "TESObjectREFR"));
			}
			catch(...)
			{
			}

			return nullptr;
		}
		//--------------------------------------------------------------------------------
		std::string Character::GetLocationString()
		{
			BGSLocation* location = GetLocation();
			if(location != nullptr)
				return SkyrimScript::GetLocationString(location);
			return "";
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLocationId()
		{
			BGSLocation* location = GetLocation();
			if(location != nullptr)
				return SkyrimScript::GetLocationId(location);
			return 0;
		}
		//--------------------------------------------------------------------------------
		void Character::SetName(const std::string& pName)
		{
			SkyrimScript::SetName(mActor, pName);
		}
		//--------------------------------------------------------------------------------
		CActor* Character::GetActor()
		{
			return (CActor*)mActor;
		}
		//--------------------------------------------------------------------------------
		void Character::SetActor(CActor* pActor)
		{
			mActor = (FreeScript::Actor*)pActor;
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMountId()
		{
			if (IsRidding())
			{
				CActor * lMount = ::Game::GetPlayersLastRiddenHorse();
				if(lMount)
				{
					return Form::GetFormID(ObjectReference::GetBaseObject((TESObjectREFR*)lMount));
				}
			}

			return 0;
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetCarryWeight()
		{
			return Actor::GetActorValue((CActor*)mActor, "CarryWeight");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMood()
		{
			return Actor::GetActorValue((CActor*)mActor, "Mood");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAssistance()
		{
			return Actor::GetActorValue((CActor*)mActor, "Assistance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnergy()
		{
			return Actor::GetActorValue((CActor*)mActor, "Energy");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMorality()
		{
			return Actor::GetActorValue((CActor*)mActor, "Morality");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetOneHanded()
		{
			return Actor::GetActorValue((CActor*)mActor, "OneHanded");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetTwoHanded()
		{
			return Actor::GetActorValue((CActor*)mActor, "TwoHanded");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMarksman()
		{
			return Actor::GetActorValue((CActor*)mActor, "Marksman");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBlock()
		{
			return Actor::GetActorValue((CActor*)mActor, "Block");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSmithing()
		{
			return Actor::GetActorValue((CActor*)mActor, "Smithing");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHeavyArmor()
		{
			return Actor::GetActorValue((CActor*)mActor, "HeavyArmor");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLightArmor()
		{
			return Actor::GetActorValue((CActor*)mActor, "LightArmor");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPickpocket()
		{
			return Actor::GetActorValue((CActor*)mActor, "Pickpocket");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLockpicking()
		{
			return Actor::GetActorValue((CActor*)mActor, "Lockpicking");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSneak()
		{
			return Actor::GetActorValue((CActor*)mActor, "Sneak");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlchemy()
		{
			return Actor::GetActorValue((CActor*)mActor, "Alchemy");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSpeechcraft()
		{
			return Actor::GetActorValue((CActor*)mActor, "Speechcraft");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlteration()
		{
			return Actor::GetActorValue((CActor*)mActor, "Alteration");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetConjuration()
		{
			return Actor::GetActorValue((CActor*)mActor, "Conjuration");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDestruction()
		{
			return Actor::GetActorValue((CActor*)mActor, "Destruction");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetIllusion()
		{
			return Actor::GetActorValue((CActor*)mActor, "Illusion");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRestoration()
		{
			return Actor::GetActorValue((CActor*)mActor, "Restoration");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnchanting()
		{
			return Actor::GetActorValue((CActor*)mActor, "Enchanting");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHealth()
		{
			return Actor::GetActorValue((CActor*)mActor, "Health");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMagicka()
		{
			return Actor::GetActorValue((CActor*)mActor, "Magicka");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetStamina()
		{
			return Actor::GetActorValue((CActor*)mActor, "Stamina");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHealRate()
		{
			return Actor::GetActorValue((CActor*)mActor, "HealRate");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMagickaRate()
		{
			return Actor::GetActorValue((CActor*)mActor, "MagickaRate");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetStaminaRate()
		{
			return Actor::GetActorValue((CActor*)mActor, "StaminaRate");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSpeedMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "SpeedMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetInventoryWeight()
		{
			return Actor::GetActorValue((CActor*)mActor, "InventoryWeight");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDragonRend()
		{
			return Actor::GetActorValue((CActor*)mActor, "DragonRend");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetCritChance()
		{
			return Actor::GetActorValue((CActor*)mActor, "CritChance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMeleeDamage()
		{
			return Actor::GetActorValue((CActor*)mActor, "MeleeDamage");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetUnarmedDamage()
		{
			return Actor::GetActorValue((CActor*)mActor, "UnarmedDamage");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMass()
		{
			return Actor::GetActorValue((CActor*)mActor, "Mass");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetVoicePoints()
		{
			return Actor::GetActorValue((CActor*)mActor, "VoicePoints");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetVoiceRate()
		{
			return Actor::GetActorValue((CActor*)mActor, "VoiceRate");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDamageResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "DamageResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPoisonResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "PoisonResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFireResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "FireResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetElectricResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "ElectricResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFrostResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "FrostResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMagicResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "MagicResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDiseaseResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "DiseaseResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetParalysis()
		{
			return Actor::GetActorValue((CActor*)mActor, "Paralysis");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetInvisibility()
		{
			return Actor::GetActorValue((CActor*)mActor, "Invisibility");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetNightEye()
		{
			return Actor::GetActorValue((CActor*)mActor, "NightEye");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDetectLifeRange()
		{
			return Actor::GetActorValue((CActor*)mActor, "DetectLifeRange");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetWaterBreathing()
		{
			return Actor::GetActorValue((CActor*)mActor, "WaterBreathing");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetWaterWalking()
		{
			return Actor::GetActorValue((CActor*)mActor, "WaterWalking");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetIgnoreCrippledLimbs()
		{
			return Actor::GetActorValue((CActor*)mActor, "IgnoreCrippledLimbs");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFame()
		{
			return Actor::GetActorValue((CActor*)mActor, "Fame");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetInfamy()
		{
			return Actor::GetActorValue((CActor*)mActor, "Infamy");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetJumpingBonus()
		{
			return Actor::GetActorValue((CActor*)mActor, "JumpingBonus");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetWardPower()
		{
			return Actor::GetActorValue((CActor*)mActor, "WardPower");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRightItemCharge()
		{
			return Actor::GetActorValue((CActor*)mActor, "RightItemCharge");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLeftItemCharge()
		{
			return Actor::GetActorValue((CActor*)mActor, "LeftItemCharge");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEquippedItemCharge()
		{
			return Actor::GetActorValue((CActor*)mActor, "EquippedItemCharge");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetArmorPerks()
		{
			return Actor::GetActorValue((CActor*)mActor, "ArmorPerks");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetShieldPerks()
		{
			return Actor::GetActorValue((CActor*)mActor, "ShieldPerks");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFavorActive()
		{
			return Actor::GetActorValue((CActor*)mActor, "FavorActive");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFavorsPerDay()
		{
			return Actor::GetActorValue((CActor*)mActor, "FavorsPerDay");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFavorsPerDayTimer()
		{
			return Actor::GetActorValue((CActor*)mActor, "FavorsPerDayTimer");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEquippedStaffCharge()
		{
			return Actor::GetActorValue((CActor*)mActor, "EquippedStaffCharge");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAbsorbChance()
		{
			return Actor::GetActorValue((CActor*)mActor, "AbsorbChance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBlindness()
		{
			return Actor::GetActorValue((CActor*)mActor, "Blindness");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetWeaponSpeedMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "WeaponSpeedMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetShoutRecoveryMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "ShoutRecoveryMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBowStaggerBonus()
		{
			return Actor::GetActorValue((CActor*)mActor, "BowStaggerBonus");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetTelekinesis()
		{
			return Actor::GetActorValue((CActor*)mActor, "Telekinesis");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetFavorPointsBonus()
		{
			return Actor::GetActorValue((CActor*)mActor, "FavorPointsBonus");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLastBribedIntimidated()
		{
			return Actor::GetActorValue((CActor*)mActor, "LastBribedIntimidated");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLastFlattered()
		{
			return Actor::GetActorValue((CActor*)mActor, "LastFlattered");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMovementNoiseMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "MovementNoiseMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBypassVendorStolenCheck()
		{
			return Actor::GetActorValue((CActor*)mActor, "BypassVendorStolenCheck");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBypassVendorKeywordCheck()
		{
			return Actor::GetActorValue((CActor*)mActor, "BypassVendorKeywordCheck");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetWaitingForPlayer()
		{
			return Actor::GetActorValue((CActor*)mActor, "WaitingForPlayer");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetOneHandedMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "OneHandedMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetTwoHandedMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "TwoHandedMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMarksmanMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "MarksmanMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBlockMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "BlockMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSmithingMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SmithingMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHeavyArmorMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "HeavyArmorMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLightArmorMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "LightArmorMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPickPocketMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "PickPocketMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLockpickingMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "LockpickingMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSneakMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SneakMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlchemyMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlchemyMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSpeechcraftMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SpeechcraftMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlterationMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlterationMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetConjurationMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "ConjurationMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDestructionMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "DestructionMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetIllusionMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "IllusionMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRestorationMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "RestorationMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnchantingMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "EnchantingMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetOneHandedSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "OneHandedSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetTwoHandedSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "TwoHandedSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMarksmanSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "MarksmanSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBlockSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "BlockSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSmithingSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "SmithingSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHeavyArmorSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "HeavyArmorSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLightArmorSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "LightArmorSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPickPocketSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "PickPocketSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLockpickingSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "LockpickingSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSneakSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "SneakSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlchemySkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlchemySkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSpeechcraftSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "SpeechcraftSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlterationSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlterationSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetConjurationSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "ConjurationSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDestructionSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "DestructionSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetIllusionSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "IllusionSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRestorationSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "RestorationSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnchantingSkillAdvance()
		{
			return Actor::GetActorValue((CActor*)mActor, "EnchantingSkillAdvance");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLeftWeaponSpeedMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "LeftWeaponSpeedMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDragonSouls()
		{
			return Actor::GetActorValue((CActor*)mActor, "DragonSouls");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetCombatHealthRegenMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "CombatHealthRegenMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetOneHandedPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "OneHandedPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetTwoHandedPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "TwoHandedPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMarksmanPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "MarksmanPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBlockPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "BlockPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSmithingPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SmithingPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHeavyArmorPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "HeavyArmorPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLightArmorPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "LightArmorPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPickPocketPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "PickPocketPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLockpickingPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "LockpickingPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSneakPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SneakPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlchemyPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlchemyPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetSpeechcraftPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "SpeechcraftPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAlterationPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "AlterationPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetConjurationPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "ConjurationPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetDestructionPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "DestructionPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetIllusionPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "IllusionPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRestorationPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "RestorationPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnchantingPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "EnchantingPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetAttackDamageMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "AttackDamageMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHealRateMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "HealRateMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMagickaRateMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "MagickaRateMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetStaminaRateMult()
		{
			return Actor::GetActorValue((CActor*)mActor, "StaminaRateMult");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetCombatHealthRegenMultMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "CombatHealthRegenMultMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetCombatHealthRegenMultPowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "CombatHealthRegenMultPowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetHealRatePowerMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "HealRatePowerMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetMagickaRateMod()
		{
			return Actor::GetActorValue((CActor*)mActor, "MagickaRateMod");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetReflectDamage()
		{
			return Actor::GetActorValue((CActor*)mActor, "ReflectDamage");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetNormalWeaponsResist()
		{
			return Actor::GetActorValue((CActor*)mActor, "NormalWeaponsResist");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetPerceptionCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "PerceptionCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetEnduranceCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "EnduranceCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLeftAttackCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "LeftAttackCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRightAttackCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "RightAttackCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetLeftMobilityCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "LeftMobilityCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetRightMobilityCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "RightMobilityCondition");
		}
		//--------------------------------------------------------------------------------
		uint32_t Character::GetBrainCondition()
		{
			return Actor::GetActorValue((CActor*)mActor, "BrainCondition");
		}

		//--------------------------------------------------------------------------------
	}
}