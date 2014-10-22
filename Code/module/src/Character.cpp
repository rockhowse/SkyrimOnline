#include "Character.h"
#include "ReferencesHelper.h"
#include "FormsHelper.h"
#include "skyscript.h"
#include "obscript.h"
#include <windows.h>

#undef GetForm


namespace Skyrim
{
	//--------------------------------------------------------------------------------
	Character::Character(Actor* pActor)
		:m_pActor(pActor)
	{
		m_FaceMorph.reserve(19);
		m_WornForms.reserve(14);
	}
	//--------------------------------------------------------------------------------
	bool Character::IsDead()
	{
		return ::Actor::IsDead((CActor*)m_pActor);
	}
	//--------------------------------------------------------------------------------
	bool Character::IsRidding()
	{
		return ::Obscript::IsRidingMount((::TESObjectREFR*)m_pActor) != 0.0;
	}
	//--------------------------------------------------------------------------------
	float Character::GetPosX()
	{
		return m_pActor->pos.X;
	}
	//--------------------------------------------------------------------------------
	float Character::GetPosY()
	{
		return m_pActor->pos.Y;
	}
	//--------------------------------------------------------------------------------
	float Character::GetPosZ()
	{
		return m_pActor->pos.Z;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotX()
	{
		return m_pActor->rot.X;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotY()
	{
		return m_pActor->rot.Y;
	}
	//--------------------------------------------------------------------------------
	float Character::GetRotZ()
	{
		return m_pActor->rot.Z;
	}
	//--------------------------------------------------------------------------------
	void Character::SetPos(float x, float y, float z)
	{
		ObjectReference::SetPosition((::TESObjectREFR*)m_pActor,x,y,z);
	}
	//--------------------------------------------------------------------------------
	void Character::SetRot(float x, float y, float z)
	{
		ObjectReference::SetAngle((::TESObjectREFR*)m_pActor, x, y, z);
	}
	//--------------------------------------------------------------------------------
	void Character::QueueNiNodeUpdate()
	{
		Skyrim::QueueNiNodeUpdate(m_pActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLevel()
	{
		return ::Actor::GetLevel((CActor*)m_pActor);
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetRace()
	{
		return TESNPCHelper(ActorHelper(m_pActor).GetNpc()).GetRaceID();
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetGender()
	{
		return ActorHelper(m_pActor).GetNpc()->gender;
	}
	//--------------------------------------------------------------------------------
	const std::vector<float>& Character::GetFaceMorph()
	{
		TESNPCHelper(ActorHelper(m_pActor).GetNpc()).GetFaceMorph(m_FaceMorph);
		return m_FaceMorph;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFaceMorph(const std::vector<float>& pFaceMorphs)
	{
		m_FaceMorph = pFaceMorphs;
		Skyrim::TESNPCHelper(ActorHelper(m_pActor).GetNpc()).SetFaceMorph(pFaceMorphs);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	const std::vector<uint32_t>& Character::GetFacePresets()
	{
		Skyrim::TESNPCHelper(ActorHelper(m_pActor).GetNpc()).GetFacePresets(m_FacePresets);
		return m_FacePresets;
	}
	//--------------------------------------------------------------------------------
	void Character::SetFacePresets(const std::vector<uint32_t>& pFacePresets)
	{
		m_FacePresets = pFacePresets;
		Skyrim::TESNPCHelper(ActorHelper(m_pActor).GetNpc()).SetFacePresets(m_FacePresets);
		this->QueueNiNodeUpdate();
	}
	//--------------------------------------------------------------------------------
	void Character::SetLevel(uint32_t level)
	{
		
	}
	//--------------------------------------------------------------------------------
	void Character::EquipItems(std::vector<uint32_t> wornForms)
	{
		::Actor::UnequipAll((CActor*)m_pActor);
		for( auto itor = wornForms.begin(); itor != wornForms.end(); ++itor )
		{
			if( *itor != 0 )
			{
				//f << std::hex << mActor << " " << ::Game::GetFormById(*itor) << std::endl;
				//f << "AddItem" << ::ObjectReference::AddItem(rtti_cast(mActor, Actor, TESObjectREFR), ::Game::GetFormById(*itor), 1, true) << std::endl;
				//SActor::EquipItem(mActor, Game::GetForm(*itor), true, false); 
			}
		}
	}
	//--------------------------------------------------------------------------------
	TESForm* Character::GetWornForm(uint32_t mask)
	{
		return (TESForm*)Skyrim::GetWornForm(m_pActor,mask);
	}
	//--------------------------------------------------------------------------------
	const std::vector<uint32_t>& Character::GetAllWornForms()
	{
		m_WornForms.clear();
		for(uint32_t i=0; i <= 13; i++)
		{
			TESForm* pForm = this->GetWornForm(1 << i);
			if( pForm != nullptr )
			{
				m_WornForms.push_back(pForm->formID);
			}
			else
			{
				m_WornForms.push_back(0);
			}
		}
		return m_WornForms;
	}
	//--------------------------------------------------------------------------------
	BGSLocation* Character::GetLocation()
	{
		try{
			return (BGSLocation*)ObjectReference::GetCurrentLocation((::TESObjectREFR*)rtti_cast(m_pActor, Actor, TESObjectREFR));
		}
		catch(...)
		{
		}

		return nullptr;
	}
	//--------------------------------------------------------------------------------
	std::string Character::GetLocationString()
	{
		Skyrim::BGSLocation* location = (Skyrim::BGSLocation*)GetLocation();
		if(location != nullptr)
			return Skyrim::BGSLocationHelper(location).GetName();
		return "";
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetLocationId()
	{
		Skyrim::BGSLocation* location = (Skyrim::BGSLocation*)GetLocation();
		if(location != nullptr)
			return location->formID;
		return 0;
	}
	//--------------------------------------------------------------------------------
	void Character::SetName(const std::string& pName)
	{
		Skyrim::SetName(m_pActor, pName);
	}
	//--------------------------------------------------------------------------------
	Actor* Character::GetActor()
	{
		return m_pActor;
	}
	//--------------------------------------------------------------------------------
	void Character::SetActor(Actor* pActor)
	{
		m_pActor = pActor;
	}
	//--------------------------------------------------------------------------------
	uint32_t Character::GetMountId()
	{
		if (IsRidding())
		{
			Actor * lMount = (Actor*)Game::GetPlayersLastRiddenHorse();
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
		return ::Actor::GetActorValue((CActor*)m_pActor, "CarryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMood()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Mood");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAssistance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Assistance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnergy()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Energy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMorality()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Morality");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHanded()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "OneHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHanded()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "TwoHanded");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksman()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Marksman");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlock()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Block");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithing()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Smithing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmor()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HeavyArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmor()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LightArmor");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickpocket()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Pickpocket");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpicking()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Lockpicking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneak()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Sneak");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemy()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Alchemy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraft()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Speechcraft");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlteration()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Alteration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjuration()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Conjuration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestruction()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Destruction");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusion()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Illusion");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestoration()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Restoration");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchanting()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Enchanting");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealth()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Health");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicka()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Magicka");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStamina()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Stamina");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRate()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HealRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRate()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MagickaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRate()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "StaminaRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeedMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInventoryWeight()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "InventoryWeight");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonRend()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DragonRend");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCritChance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "CritChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMeleeDamage()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MeleeDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetUnarmedDamage()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "UnarmedDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMass()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Mass");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoicePoints()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "VoicePoints");
	}
	//--------------------------------------------------------------------------------
	float Character::GetVoiceRate()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "VoiceRate");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDamageResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DamageResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPoisonResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "PoisonResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFireResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FireResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetElectricResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ElectricResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFrostResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FrostResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagicResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MagicResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDiseaseResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DiseaseResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetParalysis()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Paralysis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInvisibility()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Invisibility");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNightEye()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "NightEye");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDetectLifeRange()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DetectLifeRange");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterBreathing()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "WaterBreathing");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaterWalking()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "WaterWalking");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIgnoreCrippledLimbs()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "IgnoreCrippledLimbs");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFame()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Fame");
	}
	//--------------------------------------------------------------------------------
	float Character::GetInfamy()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Infamy");
	}
	//--------------------------------------------------------------------------------
	float Character::GetJumpingBonus()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "JumpingBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWardPower()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "WardPower");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightItemCharge()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RightItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftItemCharge()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LeftItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedItemCharge()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EquippedItemCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetArmorPerks()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ArmorPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShieldPerks()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ShieldPerks");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorActive()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FavorActive");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDay()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FavorsPerDay");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorsPerDayTimer()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FavorsPerDayTimer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEquippedStaffCharge()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EquippedStaffCharge");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAbsorbChance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AbsorbChance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlindness()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Blindness");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWeaponSpeedMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "WeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetShoutRecoveryMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ShoutRecoveryMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBowStaggerBonus()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BowStaggerBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTelekinesis()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "Telekinesis");
	}
	//--------------------------------------------------------------------------------
	float Character::GetFavorPointsBonus()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "FavorPointsBonus");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastBribedIntimidated()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LastBribedIntimidated");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLastFlattered()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LastFlattered");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMovementNoiseMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MovementNoiseMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorStolenCheck()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BypassVendorStolenCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBypassVendorKeywordCheck()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BypassVendorKeywordCheck");
	}
	//--------------------------------------------------------------------------------
	float Character::GetWaitingForPlayer()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "WaitingForPlayer");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "OneHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "TwoHandedMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MarksmanMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BlockMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SmithingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HeavyArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LightArmorMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "PickPocketMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LockpickingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SneakMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlchemyMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SpeechcraftMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlterationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ConjurationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DestructionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "IllusionMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RestorationMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EnchantingMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "OneHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "TwoHandedSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MarksmanSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BlockSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SmithingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HeavyArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LightArmorSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "PickPocketSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LockpickingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SneakSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemySkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlchemySkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SpeechcraftSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlterationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ConjurationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DestructionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "IllusionSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RestorationSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingSkillAdvance()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EnchantingSkillAdvance");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftWeaponSpeedMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LeftWeaponSpeedMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDragonSouls()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DragonSouls");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "CombatHealthRegenMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetOneHandedPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "OneHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetTwoHandedPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "TwoHandedPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMarksmanPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MarksmanPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBlockPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BlockPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSmithingPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SmithingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHeavyArmorPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HeavyArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLightArmorPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LightArmorPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPickPocketPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "PickPocketPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLockpickingPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LockpickingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSneakPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SneakPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlchemyPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlchemyPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetSpeechcraftPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "SpeechcraftPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAlterationPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AlterationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetConjurationPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ConjurationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetDestructionPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "DestructionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetIllusionPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "IllusionPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRestorationPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RestorationPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnchantingPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EnchantingPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetAttackDamageMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "AttackDamageMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRateMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HealRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MagickaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetStaminaRateMult()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "StaminaRateMult");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "CombatHealthRegenMultMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetCombatHealthRegenMultPowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "CombatHealthRegenMultPowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetHealRatePowerMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "HealRatePowerMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetMagickaRateMod()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "MagickaRateMod");
	}
	//--------------------------------------------------------------------------------
	float Character::GetReflectDamage()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "ReflectDamage");
	}
	//--------------------------------------------------------------------------------
	float Character::GetNormalWeaponsResist()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "NormalWeaponsResist");
	}
	//--------------------------------------------------------------------------------
	float Character::GetPerceptionCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "PerceptionCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetEnduranceCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "EnduranceCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftAttackCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LeftAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightAttackCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RightAttackCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetLeftMobilityCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "LeftMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetRightMobilityCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "RightMobilityCondition");
	}
	//--------------------------------------------------------------------------------
	float Character::GetBrainCondition()
	{
		return ::Actor::GetActorValue((CActor*)m_pActor, "BrainCondition");
	}

	//--------------------------------------------------------------------------------
}