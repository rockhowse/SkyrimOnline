#include "StdAfx.h"
#include "Character.hpp"
#include "ReferencesHelper.hpp"
#include "FormsHelper.hpp"
#include <common/skyscript.h>
#include <common/obscript.h>
#include <windows.h>

#undef GetForm


namespace FreeScript
{
	//--------------------------------------------------------------------------------
	Character::Character(Actor* pActor)
		:mActor(pActor)
	{
		mFaceMorph.reserve(19);
		mWornForms.reserve(14);
	}
	//--------------------------------------------------------------------------------
	bool Character::IsDead()
	{
		return SActor::IsDead(mActor);
	}
	//--------------------------------------------------------------------------------
	bool Character::IsRidding()
	{
		return ::Obscript::IsRidingMount(mActor) != 0.0;
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
	::Math::Vector3 Character::GetPosition()
	{
		::Math::Vector3 vec = {GetPosX(), GetPosY(), GetPosZ()};
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
	::Math::Vector3 Character::GetRotation()
	{
		::Math::Vector3 vec = {GetRotX(), GetRotY(), GetRotZ()};
		return vec;
	}
	//--------------------------------------------------------------------------------
	void Character::SetPos(float x, float y, float z)
	{
		ObjectReference::SetPosition(mActor,x,y,z);
	}
	//--------------------------------------------------------------------------------
	void Character::SetRot(float x, float y, float z)
	{
		ObjectReference::SetAngle(mActor, x,y,z);
	}
	//--------------------------------------------------------------------------------
	void Character::QueueNiNodeUpdate()
	{
		FreeScript::QueueNiNodeUpdate(mActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLevel()
	{
		return SActor::GetLevel(mActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRace()
	{
		return TESNPCHelper(ActorHelper(mActor).GetNpc()).GetRaceID();
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetGender()
	{
		return ActorHelper(mActor).GetNpc()->gender;
	}
	//--------------------------------------------------------------------------------
	const std::vector<float>& Character::GetFaceMorph()
	{
		TESNPCHelper(ActorHelper(mActor).GetNpc()).GetFaceMorph(mFaceMorph);
		return mFaceMorph;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFaceMorph(const std::vector<float>& pFaceMorphs)
	{
		mFaceMorph = pFaceMorphs;
		FreeScript::TESNPCHelper(ActorHelper(mActor).GetNpc()).SetFaceMorph(pFaceMorphs);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	const std::vector<uint32_t>& Character::GetFacePresets()
	{
		FreeScript::TESNPCHelper(ActorHelper(mActor).GetNpc()).GetFacePresets(mFacePresets);
		return mFacePresets;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFacePresets(const std::vector<uint32_t>& pFacePresets)
	{
		mFacePresets = pFacePresets;
		FreeScript::TESNPCHelper(ActorHelper(mActor).GetNpc()).SetFacePresets(mFacePresets);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	void Character::SetLevel(uint32_t level)
	{
		
	}
	//--------------------------------------------------------------------------------
	void Character::EquipItems(std::vector<uint32_t> wornForms)
	{
		std::ofstream f("Equip.log", std::ios::app);
		::SActor::UnequipAll(mActor);
		f << GetCurrentThreadId() << std::endl;
		for( auto itor = wornForms.begin(); itor != wornForms.end(); ++itor )
		{
			if( *itor != 0 )
			{
				f << std::hex << mActor << " " << ::Game::GetFormById(*itor) << std::endl;
				f << "AddItem" << ::ObjectReference::AddItem(rtti_cast(mActor, Actor, TESObjectREFR), ::Game::GetFormById(*itor), 1, true) << std::endl;
				//SActor::EquipItem(mActor, Game::GetForm(*itor), true, false); 
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
			return ObjectReference::GetCurrentLocation(rtti_cast(mActor, Actor, TESObjectREFR));
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
	Actor* Character::GetActor()
	{
		return mActor;
	}
	//--------------------------------------------------------------------------------
	void Character::SetActor(Actor* pActor)
	{
		mActor = pActor;
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMountId()
	{
		if (IsRidding())
		{
			Actor * lMount = Game::GetPlayersLastRiddenHorse();
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
		return SActor::GetActorValue(mActor, "CarryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMood()
	{
		return SActor::GetActorValue(mActor, "Mood");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAssistance()
	{
		return SActor::GetActorValue(mActor, "Assistance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnergy()
	{
		return SActor::GetActorValue(mActor, "Energy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMorality()
	{
		return SActor::GetActorValue(mActor, "Morality");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHanded()
	{
		return SActor::GetActorValue(mActor, "OneHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHanded()
	{
		return SActor::GetActorValue(mActor, "TwoHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksman()
	{
		return SActor::GetActorValue(mActor, "Marksman");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlock()
	{
		return SActor::GetActorValue(mActor, "Block");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithing()
	{
		return SActor::GetActorValue(mActor, "Smithing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmor()
	{
		return SActor::GetActorValue(mActor, "HeavyArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmor()
	{
		return SActor::GetActorValue(mActor, "LightArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickpocket()
	{
		return SActor::GetActorValue(mActor, "Pickpocket");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpicking()
	{
		return SActor::GetActorValue(mActor, "Lockpicking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneak()
	{
		return SActor::GetActorValue(mActor, "Sneak");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemy()
	{
		return SActor::GetActorValue(mActor, "Alchemy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraft()
	{
		return SActor::GetActorValue(mActor, "Speechcraft");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlteration()
	{
		return SActor::GetActorValue(mActor, "Alteration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjuration()
	{
		return SActor::GetActorValue(mActor, "Conjuration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestruction()
	{
		return SActor::GetActorValue(mActor, "Destruction");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusion()
	{
		return SActor::GetActorValue(mActor, "Illusion");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestoration()
	{
		return SActor::GetActorValue(mActor, "Restoration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchanting()
	{
		return SActor::GetActorValue(mActor, "Enchanting");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealth()
	{
		return SActor::GetActorValue(mActor, "Health");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicka()
	{
		return SActor::GetActorValue(mActor, "Magicka");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStamina()
	{
		return SActor::GetActorValue(mActor, "Stamina");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRate()
	{
		return SActor::GetActorValue(mActor, "HealRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRate()
	{
		return SActor::GetActorValue(mActor, "MagickaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRate()
	{
		return SActor::GetActorValue(mActor, "StaminaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeedMult()
	{
		return SActor::GetActorValue(mActor, "SpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInventoryWeight()
	{
		return SActor::GetActorValue(mActor, "InventoryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonRend()
	{
		return SActor::GetActorValue(mActor, "DragonRend");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCritChance()
	{
		return SActor::GetActorValue(mActor, "CritChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMeleeDamage()
	{
		return SActor::GetActorValue(mActor, "MeleeDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetUnarmedDamage()
	{
		return SActor::GetActorValue(mActor, "UnarmedDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMass()
	{
		return SActor::GetActorValue(mActor, "Mass");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoicePoints()
	{
		return SActor::GetActorValue(mActor, "VoicePoints");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoiceRate()
	{
		return SActor::GetActorValue(mActor, "VoiceRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDamageResist()
	{
		return SActor::GetActorValue(mActor, "DamageResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPoisonResist()
	{
		return SActor::GetActorValue(mActor, "PoisonResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFireResist()
	{
		return SActor::GetActorValue(mActor, "FireResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetElectricResist()
	{
		return SActor::GetActorValue(mActor, "ElectricResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFrostResist()
	{
		return SActor::GetActorValue(mActor, "FrostResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicResist()
	{
		return SActor::GetActorValue(mActor, "MagicResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDiseaseResist()
	{
		return SActor::GetActorValue(mActor, "DiseaseResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetParalysis()
	{
		return SActor::GetActorValue(mActor, "Paralysis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInvisibility()
	{
		return SActor::GetActorValue(mActor, "Invisibility");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNightEye()
	{
		return SActor::GetActorValue(mActor, "NightEye");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDetectLifeRange()
	{
		return SActor::GetActorValue(mActor, "DetectLifeRange");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterBreathing()
	{
		return SActor::GetActorValue(mActor, "WaterBreathing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterWalking()
	{
		return SActor::GetActorValue(mActor, "WaterWalking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIgnoreCrippledLimbs()
	{
		return SActor::GetActorValue(mActor, "IgnoreCrippledLimbs");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFame()
	{
		return SActor::GetActorValue(mActor, "Fame");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInfamy()
	{
		return SActor::GetActorValue(mActor, "Infamy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetJumpingBonus()
	{
		return SActor::GetActorValue(mActor, "JumpingBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWardPower()
	{
		return SActor::GetActorValue(mActor, "WardPower");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightItemCharge()
	{
		return SActor::GetActorValue(mActor, "RightItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftItemCharge()
	{
		return SActor::GetActorValue(mActor, "LeftItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedItemCharge()
	{
		return SActor::GetActorValue(mActor, "EquippedItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetArmorPerks()
	{
		return SActor::GetActorValue(mActor, "ArmorPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShieldPerks()
	{
		return SActor::GetActorValue(mActor, "ShieldPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorActive()
	{
		return SActor::GetActorValue(mActor, "FavorActive");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDay()
	{
		return SActor::GetActorValue(mActor, "FavorsPerDay");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDayTimer()
	{
		return SActor::GetActorValue(mActor, "FavorsPerDayTimer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedStaffCharge()
	{
		return SActor::GetActorValue(mActor, "EquippedStaffCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAbsorbChance()
	{
		return SActor::GetActorValue(mActor, "AbsorbChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlindness()
	{
		return SActor::GetActorValue(mActor, "Blindness");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWeaponSpeedMult()
	{
		return SActor::GetActorValue(mActor, "WeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShoutRecoveryMult()
	{
		return SActor::GetActorValue(mActor, "ShoutRecoveryMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBowStaggerBonus()
	{
		return SActor::GetActorValue(mActor, "BowStaggerBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTelekinesis()
	{
		return SActor::GetActorValue(mActor, "Telekinesis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorPointsBonus()
	{
		return SActor::GetActorValue(mActor, "FavorPointsBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastBribedIntimidated()
	{
		return SActor::GetActorValue(mActor, "LastBribedIntimidated");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastFlattered()
	{
		return SActor::GetActorValue(mActor, "LastFlattered");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMovementNoiseMult()
	{
		return SActor::GetActorValue(mActor, "MovementNoiseMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorStolenCheck()
	{
		return SActor::GetActorValue(mActor, "BypassVendorStolenCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorKeywordCheck()
	{
		return SActor::GetActorValue(mActor, "BypassVendorKeywordCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaitingForPlayer()
	{
		return SActor::GetActorValue(mActor, "WaitingForPlayer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedMod()
	{
		return SActor::GetActorValue(mActor, "OneHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedMod()
	{
		return SActor::GetActorValue(mActor, "TwoHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanMod()
	{
		return SActor::GetActorValue(mActor, "MarksmanMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockMod()
	{
		return SActor::GetActorValue(mActor, "BlockMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingMod()
	{
		return SActor::GetActorValue(mActor, "SmithingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorMod()
	{
		return SActor::GetActorValue(mActor, "HeavyArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorMod()
	{
		return SActor::GetActorValue(mActor, "LightArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketMod()
	{
		return SActor::GetActorValue(mActor, "PickPocketMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingMod()
	{
		return SActor::GetActorValue(mActor, "LockpickingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakMod()
	{
		return SActor::GetActorValue(mActor, "SneakMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyMod()
	{
		return SActor::GetActorValue(mActor, "AlchemyMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftMod()
	{
		return SActor::GetActorValue(mActor, "SpeechcraftMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationMod()
	{
		return SActor::GetActorValue(mActor, "AlterationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationMod()
	{
		return SActor::GetActorValue(mActor, "ConjurationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionMod()
	{
		return SActor::GetActorValue(mActor, "DestructionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionMod()
	{
		return SActor::GetActorValue(mActor, "IllusionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationMod()
	{
		return SActor::GetActorValue(mActor, "RestorationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingMod()
	{
		return SActor::GetActorValue(mActor, "EnchantingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "OneHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "TwoHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "MarksmanSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "BlockSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "SmithingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "HeavyArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "LightArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "PickPocketSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "LockpickingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "SneakSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemySkillAdvance()
	{
		return SActor::GetActorValue(mActor, "AlchemySkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "SpeechcraftSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "AlterationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "ConjurationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "DestructionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "IllusionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "RestorationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingSkillAdvance()
	{
		return SActor::GetActorValue(mActor, "EnchantingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftWeaponSpeedMult()
	{
		return SActor::GetActorValue(mActor, "LeftWeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonSouls()
	{
		return SActor::GetActorValue(mActor, "DragonSouls");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMult()
	{
		return SActor::GetActorValue(mActor, "CombatHealthRegenMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedPowerMod()
	{
		return SActor::GetActorValue(mActor, "OneHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedPowerMod()
	{
		return SActor::GetActorValue(mActor, "TwoHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanPowerMod()
	{
		return SActor::GetActorValue(mActor, "MarksmanPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockPowerMod()
	{
		return SActor::GetActorValue(mActor, "BlockPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingPowerMod()
	{
		return SActor::GetActorValue(mActor, "SmithingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorPowerMod()
	{
		return SActor::GetActorValue(mActor, "HeavyArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorPowerMod()
	{
		return SActor::GetActorValue(mActor, "LightArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketPowerMod()
	{
		return SActor::GetActorValue(mActor, "PickPocketPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingPowerMod()
	{
		return SActor::GetActorValue(mActor, "LockpickingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakPowerMod()
	{
		return SActor::GetActorValue(mActor, "SneakPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyPowerMod()
	{
		return SActor::GetActorValue(mActor, "AlchemyPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftPowerMod()
	{
		return SActor::GetActorValue(mActor, "SpeechcraftPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationPowerMod()
	{
		return SActor::GetActorValue(mActor, "AlterationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationPowerMod()
	{
		return SActor::GetActorValue(mActor, "ConjurationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionPowerMod()
	{
		return SActor::GetActorValue(mActor, "DestructionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionPowerMod()
	{
		return SActor::GetActorValue(mActor, "IllusionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationPowerMod()
	{
		return SActor::GetActorValue(mActor, "RestorationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingPowerMod()
	{
		return SActor::GetActorValue(mActor, "EnchantingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAttackDamageMult()
	{
		return SActor::GetActorValue(mActor, "AttackDamageMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRateMult()
	{
		return SActor::GetActorValue(mActor, "HealRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMult()
	{
		return SActor::GetActorValue(mActor, "MagickaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRateMult()
	{
		return SActor::GetActorValue(mActor, "StaminaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultMod()
	{
		return SActor::GetActorValue(mActor, "CombatHealthRegenMultMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultPowerMod()
	{
		return SActor::GetActorValue(mActor, "CombatHealthRegenMultPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRatePowerMod()
	{
		return SActor::GetActorValue(mActor, "HealRatePowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMod()
	{
		return SActor::GetActorValue(mActor, "MagickaRateMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetReflectDamage()
	{
		return SActor::GetActorValue(mActor, "ReflectDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNormalWeaponsResist()
	{
		return SActor::GetActorValue(mActor, "NormalWeaponsResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPerceptionCondition()
	{
		return SActor::GetActorValue(mActor, "PerceptionCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnduranceCondition()
	{
		return SActor::GetActorValue(mActor, "EnduranceCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftAttackCondition()
	{
		return SActor::GetActorValue(mActor, "LeftAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightAttackCondition()
	{
		return SActor::GetActorValue(mActor, "RightAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftMobilityCondition()
	{
		return SActor::GetActorValue(mActor, "LeftMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightMobilityCondition()
	{
		return SActor::GetActorValue(mActor, "RightMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBrainCondition()
	{
		return SActor::GetActorValue(mActor, "BrainCondition");
	}

	//--------------------------------------------------------------------------------
}