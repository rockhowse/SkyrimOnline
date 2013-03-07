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
		return mActor->pos.X;
	}
	//--------------------------------------------------------------------------------
	float Character::GetPosY()
	{
		return mActor->pos.Y;
	}
	//--------------------------------------------------------------------------------
	float Character::GetPosZ()
	{
		return mActor->pos.Z;
	}
	//--------------------------------------------------------------------------------
	Vector3 Character::GetPosition()
	{
		Vector3 vec = {GetPosX(), GetPosY(), GetPosZ()};
		return vec;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotX()
	{
		return mActor->rot.X;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotY()
	{
		return mActor->rot.Y;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotZ()
	{
		return mActor->rot.Z;
	}
	//--------------------------------------------------------------------------------
	Vector3 Character::GetRotation()
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
		return ((uint8_t(__thiscall*)(FreeScript::TESNPC*))0x0055ABD0)(FreeScript::ActorHelper(mActor).GetNpc());
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
	const std::vector<uint32_t>& Character::GetFacePresets()
	{
		FreeScript::TESNPCHelper(FreeScript::ActorHelper(mActor).GetNpc()).GetFacePresets(mFacePresets);
		return mFacePresets;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFacePresets(const std::vector<uint32_t>& pFacePresets)
	{
		mFacePresets = pFacePresets;
		FreeScript::TESNPCHelper(FreeScript::ActorHelper(mActor).GetNpc()).SetFacePresets(mFacePresets);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	void Character::SetLevel(uint32_t level)
	{
		
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
	float Character::GetCarryWeight()
	{
		return ::Actor::GetActorValue(mActor, "CarryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMood()
	{
		return ::Actor::GetActorValue(mActor, "Mood");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAssistance()
	{
		return ::Actor::GetActorValue(mActor, "Assistance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnergy()
	{
		return ::Actor::GetActorValue(mActor, "Energy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMorality()
	{
		return ::Actor::GetActorValue(mActor, "Morality");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHanded()
	{
		return ::Actor::GetActorValue(mActor, "OneHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHanded()
	{
		return ::Actor::GetActorValue(mActor, "TwoHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksman()
	{
		return ::Actor::GetActorValue(mActor, "Marksman");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlock()
	{
		return ::Actor::GetActorValue(mActor, "Block");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithing()
	{
		return ::Actor::GetActorValue(mActor, "Smithing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmor()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmor()
	{
		return ::Actor::GetActorValue(mActor, "LightArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickpocket()
	{
		return ::Actor::GetActorValue(mActor, "Pickpocket");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpicking()
	{
		return ::Actor::GetActorValue(mActor, "Lockpicking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneak()
	{
		return ::Actor::GetActorValue(mActor, "Sneak");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemy()
	{
		return ::Actor::GetActorValue(mActor, "Alchemy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraft()
	{
		return ::Actor::GetActorValue(mActor, "Speechcraft");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlteration()
	{
		return ::Actor::GetActorValue(mActor, "Alteration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjuration()
	{
		return ::Actor::GetActorValue(mActor, "Conjuration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestruction()
	{
		return ::Actor::GetActorValue(mActor, "Destruction");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusion()
	{
		return ::Actor::GetActorValue(mActor, "Illusion");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestoration()
	{
		return ::Actor::GetActorValue(mActor, "Restoration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchanting()
	{
		return ::Actor::GetActorValue(mActor, "Enchanting");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealth()
	{
		return ::Actor::GetActorValue(mActor, "Health");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicka()
	{
		return ::Actor::GetActorValue(mActor, "Magicka");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStamina()
	{
		return ::Actor::GetActorValue(mActor, "Stamina");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRate()
	{
		return ::Actor::GetActorValue(mActor, "HealRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRate()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRate()
	{
		return ::Actor::GetActorValue(mActor, "StaminaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "SpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInventoryWeight()
	{
		return ::Actor::GetActorValue(mActor, "InventoryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonRend()
	{
		return ::Actor::GetActorValue(mActor, "DragonRend");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCritChance()
	{
		return ::Actor::GetActorValue(mActor, "CritChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMeleeDamage()
	{
		return ::Actor::GetActorValue(mActor, "MeleeDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetUnarmedDamage()
	{
		return ::Actor::GetActorValue(mActor, "UnarmedDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMass()
	{
		return ::Actor::GetActorValue(mActor, "Mass");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoicePoints()
	{
		return ::Actor::GetActorValue(mActor, "VoicePoints");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoiceRate()
	{
		return ::Actor::GetActorValue(mActor, "VoiceRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDamageResist()
	{
		return ::Actor::GetActorValue(mActor, "DamageResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPoisonResist()
	{
		return ::Actor::GetActorValue(mActor, "PoisonResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFireResist()
	{
		return ::Actor::GetActorValue(mActor, "FireResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetElectricResist()
	{
		return ::Actor::GetActorValue(mActor, "ElectricResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFrostResist()
	{
		return ::Actor::GetActorValue(mActor, "FrostResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicResist()
	{
		return ::Actor::GetActorValue(mActor, "MagicResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDiseaseResist()
	{
		return ::Actor::GetActorValue(mActor, "DiseaseResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetParalysis()
	{
		return ::Actor::GetActorValue(mActor, "Paralysis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInvisibility()
	{
		return ::Actor::GetActorValue(mActor, "Invisibility");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNightEye()
	{
		return ::Actor::GetActorValue(mActor, "NightEye");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDetectLifeRange()
	{
		return ::Actor::GetActorValue(mActor, "DetectLifeRange");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterBreathing()
	{
		return ::Actor::GetActorValue(mActor, "WaterBreathing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterWalking()
	{
		return ::Actor::GetActorValue(mActor, "WaterWalking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIgnoreCrippledLimbs()
	{
		return ::Actor::GetActorValue(mActor, "IgnoreCrippledLimbs");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFame()
	{
		return ::Actor::GetActorValue(mActor, "Fame");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInfamy()
	{
		return ::Actor::GetActorValue(mActor, "Infamy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetJumpingBonus()
	{
		return ::Actor::GetActorValue(mActor, "JumpingBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWardPower()
	{
		return ::Actor::GetActorValue(mActor, "WardPower");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "RightItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "LeftItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedItemCharge()
	{
		return ::Actor::GetActorValue(mActor, "EquippedItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetArmorPerks()
	{
		return ::Actor::GetActorValue(mActor, "ArmorPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShieldPerks()
	{
		return ::Actor::GetActorValue(mActor, "ShieldPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorActive()
	{
		return ::Actor::GetActorValue(mActor, "FavorActive");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDay()
	{
		return ::Actor::GetActorValue(mActor, "FavorsPerDay");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDayTimer()
	{
		return ::Actor::GetActorValue(mActor, "FavorsPerDayTimer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedStaffCharge()
	{
		return ::Actor::GetActorValue(mActor, "EquippedStaffCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAbsorbChance()
	{
		return ::Actor::GetActorValue(mActor, "AbsorbChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlindness()
	{
		return ::Actor::GetActorValue(mActor, "Blindness");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWeaponSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "WeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShoutRecoveryMult()
	{
		return ::Actor::GetActorValue(mActor, "ShoutRecoveryMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBowStaggerBonus()
	{
		return ::Actor::GetActorValue(mActor, "BowStaggerBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTelekinesis()
	{
		return ::Actor::GetActorValue(mActor, "Telekinesis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorPointsBonus()
	{
		return ::Actor::GetActorValue(mActor, "FavorPointsBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastBribedIntimidated()
	{
		return ::Actor::GetActorValue(mActor, "LastBribedIntimidated");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastFlattered()
	{
		return ::Actor::GetActorValue(mActor, "LastFlattered");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMovementNoiseMult()
	{
		return ::Actor::GetActorValue(mActor, "MovementNoiseMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorStolenCheck()
	{
		return ::Actor::GetActorValue(mActor, "BypassVendorStolenCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorKeywordCheck()
	{
		return ::Actor::GetActorValue(mActor, "BypassVendorKeywordCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaitingForPlayer()
	{
		return ::Actor::GetActorValue(mActor, "WaitingForPlayer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedMod()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedMod()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanMod()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockMod()
	{
		return ::Actor::GetActorValue(mActor, "BlockMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingMod()
	{
		return ::Actor::GetActorValue(mActor, "SmithingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorMod()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorMod()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketMod()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingMod()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakMod()
	{
		return ::Actor::GetActorValue(mActor, "SneakMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyMod()
	{
		return ::Actor::GetActorValue(mActor, "AlchemyMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftMod()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationMod()
	{
		return ::Actor::GetActorValue(mActor, "AlterationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationMod()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionMod()
	{
		return ::Actor::GetActorValue(mActor, "DestructionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionMod()
	{
		return ::Actor::GetActorValue(mActor, "IllusionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationMod()
	{
		return ::Actor::GetActorValue(mActor, "RestorationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingMod()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "BlockSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SmithingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SneakSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemySkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "AlchemySkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "AlterationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "DestructionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "IllusionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "RestorationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingSkillAdvance()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftWeaponSpeedMult()
	{
		return ::Actor::GetActorValue(mActor, "LeftWeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonSouls()
	{
		return ::Actor::GetActorValue(mActor, "DragonSouls");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMult()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "OneHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "TwoHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "MarksmanPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "BlockPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SmithingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "HeavyArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "LightArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "PickPocketPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "LockpickingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SneakPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "AlchemyPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "SpeechcraftPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "AlterationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "ConjurationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "DestructionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "IllusionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "RestorationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "EnchantingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAttackDamageMult()
	{
		return ::Actor::GetActorValue(mActor, "AttackDamageMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRateMult()
	{
		return ::Actor::GetActorValue(mActor, "HealRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMult()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRateMult()
	{
		return ::Actor::GetActorValue(mActor, "StaminaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultMod()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMultMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultPowerMod()
	{
		return ::Actor::GetActorValue(mActor, "CombatHealthRegenMultPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRatePowerMod()
	{
		return ::Actor::GetActorValue(mActor, "HealRatePowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMod()
	{
		return ::Actor::GetActorValue(mActor, "MagickaRateMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetReflectDamage()
	{
		return ::Actor::GetActorValue(mActor, "ReflectDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNormalWeaponsResist()
	{
		return ::Actor::GetActorValue(mActor, "NormalWeaponsResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPerceptionCondition()
	{
		return ::Actor::GetActorValue(mActor, "PerceptionCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnduranceCondition()
	{
		return ::Actor::GetActorValue(mActor, "EnduranceCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftAttackCondition()
	{
		return ::Actor::GetActorValue(mActor, "LeftAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightAttackCondition()
	{
		return ::Actor::GetActorValue(mActor, "RightAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftMobilityCondition()
	{
		return ::Actor::GetActorValue(mActor, "LeftMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightMobilityCondition()
	{
		return ::Actor::GetActorValue(mActor, "RightMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBrainCondition()
	{
		return ::Actor::GetActorValue(mActor, "BrainCondition");
	}

	//--------------------------------------------------------------------------------
}