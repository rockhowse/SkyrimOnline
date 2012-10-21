#include "stdafx.h"
#include "Character.hpp"
#include "ReferencesHelper.hpp"
#include "FormsHelper.hpp"

namespace FreeScript
{
	//--------------------------------------------------------------------------------
	Character::Character(FreeScript::Actor* pActor)
		:mActor(pActor)
	{
		mFaceMorph.reserve(19);
		mWornForms.reserve(14);
	}
	//--------------------------------------------------------------------------------
	bool Character::IsDead()
	{
		return ::Actor::IsDead(mActor);
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
	Character::Vector3 Character::GetPosition()
	{
		Vector3 vec = {GetPosX(), GetPosY(), GetPosZ()};
		return vec;
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
	Character::Vector3 Character::GetRotation()
	{
		Vector3 vec = {GetRotX(), GetRotY(), GetRotZ()};
		return vec;
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
		FreeScript::QueueNiNodeUpdate(mActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLevel()
	{
		return ::Actor::GetLevel(mActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRace()
	{
		return FreeScript::TESNPCHelper(FreeScript::ActorHelper(mActor).GetNpc()).GetRaceID();
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetGender()
	{
		return ActorBase::GetSex(FreeScript::ActorHelper(mActor).GetNpc());
	}
	//--------------------------------------------------------------------------------
	const std::vector<float>& Character::GetFaceMorph()
	{
		FreeScript::TESNPCHelper(FreeScript::ActorHelper(mActor).GetNpc()).GetFaceMorph(mFaceMorph);
		return mFaceMorph;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFaceMorph(const std::vector<float>& pFaceMorphs)
	{
		mFaceMorph = pFaceMorphs;
		FreeScript::TESNPCHelper(FreeScript::ActorHelper(mActor).GetNpc()).SetFaceMorph(pFaceMorphs);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	void Character::EquipItems(std::vector<uint32_t> wornForms)
	{
		::Actor::UnequipAll(mActor);
		for( auto itor = wornForms.begin(); itor != wornForms.end(); ++itor )
		{
			if( *itor != 0 )
			{
				ObjectReference::AddItem((TESObjectREFR*)dyn_cast(mActor, "CActor", "TESObjectREFR"), ::Game::GetFormById(*itor), 1, true);
				::Actor::EquipItem(mActor, ::Game::GetFormById(*itor), true, false); 
			}
		}
	}
	//--------------------------------------------------------------------------------
	TESForm* Character::GetWornForm(uint32_t mask)
	{
		return (TESForm*)FreeScript::GetWornForm(mActor,mask);
	}
	//--------------------------------------------------------------------------------
	const std::vector<uint32_t>& Character::GetAllWornForms()
	{
		mWornForms.clear();
		for(uint32_t i=0; i <= 13; i++)
		{
			TESForm* pForm = this->GetWornForm(1 << i);
			if( pForm != nullptr )
			{
				mWornForms.push_back(pForm->formID);
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
		FreeScript::BGSLocation* location = (FreeScript::BGSLocation*)GetLocation();
		if(location != nullptr)
			return FreeScript::BGSLocationHelper(location).GetName();
		return "";
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLocationId()
	{
		FreeScript::BGSLocation* location = (FreeScript::BGSLocation*)GetLocation();
		if(location != nullptr)
			return location->formID;
		return 0;
	}
	//--------------------------------------------------------------------------------
	void Character::SetName(const std::string& pName)
	{
		FreeScript::SetName(mActor, pName);
	}
	//--------------------------------------------------------------------------------
	CActor* Character::GetActor()
	{
		return mActor;
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
			FreeScript::Actor * lMount = (FreeScript::Actor*)::Game::GetPlayersLastRiddenHorse();
			if(lMount)
			{
				return lMount->baseForm->formID;
			}
		}

		return 0;
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetCarryWeight()
	{
		return ::Actor::GetActorValue(mActor, "CarryWeight");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMood()
	{
		return ::Actor::GetActorValue(mActor, "Mood");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAssistance()
	{
		return ::Actor::GetActorValue(mActor, "Assistance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnergy()
	{
		return ::Actor::GetActorValue(mActor, "Energy");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMorality()
	{
		return ::Actor::GetActorValue(mActor, "Morality");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetOneHanded()
	{
		return ::Actor::GetActorValue(mActor, "OneHanded");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetTwoHanded()
	{
		return ::Actor::GetActorValue(mActor, "TwoHanded");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMarksman()
	{
		return ::Actor::GetActorValue(mActor, "Marksman");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBlock()
	{
		return ::Actor::GetActorValue(mActor, "Block");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSmithing()
	{
		return ::Actor::GetActorValue(mActor, "Smithing");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHeavyArmor()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmor");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLightArmor()
	{
		return ::Actor::GetActorValue(mActor, "LightArmor");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPickpocket()
	{
		return ::Actor::GetActorValue(mActor, "Pickpocket");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLockpicking()
	{
		return ::Actor::GetActorValue(mActor, "Lockpicking");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSneak()
	{
		return ::Actor::GetActorValue(mActor, "Sneak");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlchemy()
	{
		return ::Actor::GetActorValue(mActor, "Alchemy");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSpeechcraft()
	{
		return ::Actor::GetActorValue(mActor, "Speechcraft");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlteration()
	{
		return ::Actor::GetActorValue(mActor, "Alteration");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetConjuration()
	{
		return ::Actor::GetActorValue(mActor, "Conjuration");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDestruction()
	{
		return ::Actor::GetActorValue(mActor, "Destruction");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetIllusion()
	{
		return ::Actor::GetActorValue(mActor, "Illusion");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRestoration()
	{
		return ::Actor::GetActorValue(mActor, "Restoration");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnchanting()
	{
		return ::Actor::GetActorValue(mActor, "Enchanting");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHealth()
	{
		return ::Actor::GetActorValue(mActor, "Health");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMagicka()
	{
		return ::Actor::GetActorValue(mActor, "Magicka");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetStamina()
	{
		return ::Actor::GetActorValue(mActor, "Stamina");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHealRate()
	{
		return ::Actor::GetActorValue(mActor, "HealRate");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMagickaRate()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRate");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetStaminaRate()
	{
		return ::Actor::GetActorValue(mActor, "StaminaRate");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "SpeedMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetInventoryWeight()
	{
		return ::Actor::GetActorValue(mActor, "InventoryWeight");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDragonRend()
	{
		return ::Actor::GetActorValue(mActor, "DragonRend");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetCritChance()
	{
		return ::Actor::GetActorValue(mActor, "CritChance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMeleeDamage()
	{
		return ::Actor::GetActorValue(mActor, "MeleeDamage");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetUnarmedDamage()
	{
		return ::Actor::GetActorValue(mActor, "UnarmedDamage");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMass()
	{
		return ::Actor::GetActorValue(mActor, "Mass");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetVoicePoints()
	{
		return ::Actor::GetActorValue(mActor, "VoicePoints");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetVoiceRate()
	{
		return ::Actor::GetActorValue(mActor, "VoiceRate");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDamageResist()
	{
		return ::Actor::GetActorValue(mActor, "DamageResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPoisonResist()
	{
		return ::Actor::GetActorValue(mActor, "PoisonResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFireResist()
	{
		return ::Actor::GetActorValue(mActor, "FireResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetElectricResist()
	{
		return ::Actor::GetActorValue(mActor, "ElectricResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFrostResist()
	{
		return ::Actor::GetActorValue(mActor, "FrostResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMagicResist()
	{
		return ::Actor::GetActorValue(mActor, "MagicResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDiseaseResist()
	{
		return ::Actor::GetActorValue(mActor, "DiseaseResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetParalysis()
	{
		return ::Actor::GetActorValue(mActor, "Paralysis");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetInvisibility()
	{
		return ::Actor::GetActorValue(mActor, "Invisibility");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetNightEye()
	{
		return ::Actor::GetActorValue(mActor, "NightEye");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDetectLifeRange()
	{
		return ::Actor::GetActorValue(mActor, "DetectLifeRange");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetWaterBreathing()
	{
		return ::Actor::GetActorValue(mActor, "WaterBreathing");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetWaterWalking()
	{
		return ::Actor::GetActorValue(mActor, "WaterWalking");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetIgnoreCrippledLimbs()
	{
		return ::Actor::GetActorValue(mActor, "IgnoreCrippledLimbs");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFame()
	{
		return ::Actor::GetActorValue(mActor, "Fame");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetInfamy()
	{
		return ::Actor::GetActorValue(mActor, "Infamy");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetJumpingBonus()
	{
		return ::Actor::GetActorValue(mActor, "JumpingBonus");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetWardPower()
	{
		return ::Actor::GetActorValue(mActor, "WardPower");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRightItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "RightItemCharge");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLeftItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "LeftItemCharge");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEquippedItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "EquippedItemCharge");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetArmorPerks()
	{
		return ::Actor::GetActorValue(mActor, "ArmorPerks");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetShieldPerks()
	{
		return ::Actor::GetActorValue(mActor, "ShieldPerks");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFavorActive()
	{
		return ::Actor::GetActorValue(mActor, "FavorActive");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFavorsPerDay()
	{
		return ::Actor::GetActorValue(mActor, "FavorsPerDay");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFavorsPerDayTimer()
	{
		return ::Actor::GetActorValue(mActor, "FavorsPerDayTimer");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEquippedStaffCharge()
	{
		return ::Actor::GetActorValue(mActor, "EquippedStaffCharge");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAbsorbChance()
	{
		return ::Actor::GetActorValue(mActor, "AbsorbChance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBlindness()
	{
		return ::Actor::GetActorValue(mActor, "Blindness");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetWeaponSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "WeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetShoutRecoveryMult()
	{
		return ::Actor::GetActorValue(mActor, "ShoutRecoveryMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBowStaggerBonus()
	{
		return ::Actor::GetActorValue(mActor, "BowStaggerBonus");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetTelekinesis()
	{
		return ::Actor::GetActorValue(mActor, "Telekinesis");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetFavorPointsBonus()
	{
		return ::Actor::GetActorValue(mActor, "FavorPointsBonus");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLastBribedIntimidated()
	{
		return ::Actor::GetActorValue(mActor, "LastBribedIntimidated");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLastFlattered()
	{
		return ::Actor::GetActorValue(mActor, "LastFlattered");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMovementNoiseMult()
	{
		return ::Actor::GetActorValue(mActor, "MovementNoiseMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBypassVendorStolenCheck()
	{
		return ::Actor::GetActorValue(mActor, "BypassVendorStolenCheck");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBypassVendorKeywordCheck()
	{
		return ::Actor::GetActorValue(mActor, "BypassVendorKeywordCheck");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetWaitingForPlayer()
	{
		return ::Actor::GetActorValue(mActor, "WaitingForPlayer");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetOneHandedMod()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetTwoHandedMod()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMarksmanMod()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBlockMod()
	{
		return ::Actor::GetActorValue(mActor, "BlockMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSmithingMod()
	{
		return ::Actor::GetActorValue(mActor, "SmithingMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHeavyArmorMod()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLightArmorMod()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPickPocketMod()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLockpickingMod()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSneakMod()
	{
		return ::Actor::GetActorValue(mActor, "SneakMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlchemyMod()
	{
		return ::Actor::GetActorValue(mActor, "AlchemyMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSpeechcraftMod()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlterationMod()
	{
		return ::Actor::GetActorValue(mActor, "AlterationMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetConjurationMod()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDestructionMod()
	{
		return ::Actor::GetActorValue(mActor, "DestructionMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetIllusionMod()
	{
		return ::Actor::GetActorValue(mActor, "IllusionMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRestorationMod()
	{
		return ::Actor::GetActorValue(mActor, "RestorationMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnchantingMod()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetOneHandedSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetTwoHandedSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMarksmanSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBlockSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "BlockSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSmithingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SmithingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHeavyArmorSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLightArmorSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPickPocketSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLockpickingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSneakSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SneakSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlchemySkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "AlchemySkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSpeechcraftSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlterationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "AlterationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetConjurationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDestructionSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "DestructionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetIllusionSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "IllusionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRestorationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "RestorationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnchantingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLeftWeaponSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "LeftWeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDragonSouls()
	{
		return ::Actor::GetActorValue(mActor, "DragonSouls");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetCombatHealthRegenMult()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetOneHandedPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetTwoHandedPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMarksmanPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBlockPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "BlockPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSmithingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SmithingPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHeavyArmorPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLightArmorPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPickPocketPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLockpickingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSneakPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SneakPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlchemyPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "AlchemyPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetSpeechcraftPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAlterationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "AlterationPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetConjurationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetDestructionPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "DestructionPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetIllusionPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "IllusionPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRestorationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "RestorationPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnchantingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetAttackDamageMult()
	{
		return ::Actor::GetActorValue(mActor, "AttackDamageMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHealRateMult()
	{
		return ::Actor::GetActorValue(mActor, "HealRateMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMagickaRateMult()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRateMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetStaminaRateMult()
	{
		return ::Actor::GetActorValue(mActor, "StaminaRateMult");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetCombatHealthRegenMultMod()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMultMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetCombatHealthRegenMultPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMultPowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetHealRatePowerMod()
	{
		return ::Actor::GetActorValue(mActor, "HealRatePowerMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMagickaRateMod()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRateMod");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetReflectDamage()
	{
		return ::Actor::GetActorValue(mActor, "ReflectDamage");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetNormalWeaponsResist()
	{
		return ::Actor::GetActorValue(mActor, "NormalWeaponsResist");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetPerceptionCondition()
	{
		return ::Actor::GetActorValue(mActor, "PerceptionCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetEnduranceCondition()
	{
		return ::Actor::GetActorValue(mActor, "EnduranceCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLeftAttackCondition()
	{
		return ::Actor::GetActorValue(mActor, "LeftAttackCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRightAttackCondition()
	{
		return ::Actor::GetActorValue(mActor, "RightAttackCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLeftMobilityCondition()
	{
		return ::Actor::GetActorValue(mActor, "LeftMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRightMobilityCondition()
	{
		return ::Actor::GetActorValue(mActor, "RightMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetBrainCondition()
	{
		return ::Actor::GetActorValue(mActor, "BrainCondition");
	}

	//--------------------------------------------------------------------------------
}