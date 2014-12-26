#include "GameForms.h"
#include "GameObjects.h"

const _LookupFormByID LookupFormByID = (_LookupFormByID)0x00451A30;

BGSDefaultObjectManager *	BGSDefaultObjectManager::GetSingleton(void)
{
	return (BGSDefaultObjectManager *)0x012E2500;
}

void TESForm::CopyFromEx(TESForm * rhsForm)
{
	if(!rhsForm || rhsForm->formType != formType)
		return;

	switch(formType)
	{
		case kFormType_CombatStyle:
		{
			TESCombatStyle	* lhs = (TESCombatStyle *)this;
			TESCombatStyle	* rhs = (TESCombatStyle *)rhsForm;

			lhs->general =				rhs->general;
			lhs->melee =				rhs->melee;
			lhs->closeRange =			rhs->closeRange;
			lhs->longRange =			rhs->longRange;
			lhs->flight =				rhs->flight;
			lhs->flags =				rhs->flags;
		}
		break;

		// Untested, probably shouldn't use this
		case kFormType_Armor:
		{
			TESObjectARMO	* lhs = (TESObjectARMO*)this;
			TESObjectARMO	* rhs = (TESObjectARMO*)rhsForm;

			lhs->fullName.CopyFromBase(&rhs->fullName);
			lhs->race.CopyFromBase(&rhs->race);
			lhs->enchantable.CopyFromBase(&rhs->enchantable);
			lhs->value.CopyFromBase(&rhs->value);
			lhs->weight.CopyFromBase(&rhs->weight);
			lhs->destructible.CopyFromBase(&rhs->destructible);
			lhs->pickupSounds.CopyFromBase(&rhs->pickupSounds);
			lhs->bipedModel.CopyFromBase(&rhs->bipedModel);
			lhs->equipType.CopyFromBase(&rhs->equipType);
			lhs->bipedObject.CopyFromBase(&rhs->bipedObject);
			lhs->blockBash.CopyFromBase(&rhs->blockBash);
			lhs->keyword.CopyFromBase(&rhs->keyword);
			lhs->description.CopyFromBase(&rhs->description);

			lhs->armorValTimes100	= rhs->armorValTimes100;
			lhs->armorAddons.CopyFrom(&rhs->armorAddons);
			lhs->templateArmor = rhs->templateArmor;
		}
		break;
		case kFormType_NPC:
		{
			TESNPC * lhs = (TESNPC*)this;
			TESNPC * rhs = (TESNPC*)rhsForm;

			// TESForm
			lhs->unk04 = rhs->unk04;
			lhs->flags = rhs->flags;
			lhs->unk10 = rhs->unk10;
			lhs->formType = rhs->formType;

			// TESBoundObject
			lhs->bounds.x = rhs->bounds.x;
			lhs->bounds.y = rhs->bounds.y;
			lhs->bounds.z = rhs->bounds.z;
			lhs->bounds2.x = rhs->bounds2.x;
			lhs->bounds2.y = rhs->bounds2.y;
			lhs->bounds2.z = rhs->bounds2.z;

			// TESActorBase
			lhs->actorData.CopyFromBase(&rhs->actorData);
			lhs->container.CopyFromBase(&rhs->container);
			lhs->spellList.CopyFromBase(&rhs->spellList);
			lhs->aiForm.CopyFromBase(&rhs->aiForm);
			lhs->fullName.CopyFromBase(&rhs->fullName);
			memcpy(&lhs->actorValueOwner, &rhs->actorValueOwner, sizeof(lhs->actorValueOwner));
			lhs->destructible.CopyFromBase(&rhs->destructible);
			lhs->skinForm.CopyFromBase(&rhs->skinForm);
			lhs->keyword.CopyFromBase(&rhs->keyword);
			lhs->attackData.CopyFromBase(&rhs->attackData);
			lhs->perkRanks.CopyFromBase(&rhs->perkRanks);

			// TESNPC
			lhs->race.CopyFromBase(&rhs->race);
			lhs->overridePacks.CopyFromBase(&rhs->overridePacks);
			memcpy(lhs->unk0E0, rhs->unk0E0, 0x12);
			memcpy(lhs->unk0F2, rhs->unk0F2, 0x12);
			memcpy(lhs->pad104, rhs->pad104, 0x10A - 0x104);

			lhs->unk10A = rhs->unk10A;
			lhs->npcClass = rhs->npcClass;
			lhs->headData = (TESNPC::HeadData *)FormHeap_Allocate(sizeof(TESNPC::HeadData));
			lhs->headData->hairColor = (BGSColorForm*)IFormFactory::GetFactoryForType(kFormType_ColorForm)->Create();
			lhs->headData->hairColor->abgr = rhs->headData->hairColor->abgr;
			lhs->headData->hairColor->flags = rhs->headData->hairColor->flags;
			lhs->headData->hairColor->formType = rhs->headData->hairColor->formType;
			lhs->headData->hairColor->fullName.CopyFromBase(&rhs->headData->hairColor->fullName);
			lhs->headData->hairColor->unk04 = rhs->headData->hairColor->unk04;
			lhs->headData->hairColor->unk10 = rhs->headData->hairColor->unk10;
			lhs->headData->headTexture = rhs->headData->headTexture;

			lhs->unk114 = rhs->unk114;
			lhs->combatStyle = rhs->combatStyle;
			lhs->unk11C = rhs->unk11C;

			lhs->overlayRace = rhs->overlayRace;
			lhs->nextTemplate = rhs->nextTemplate;
			lhs->height = rhs->height;
			lhs->weight = rhs->weight;
			lhs->pad130 = rhs->pad130;

			lhs->shortName = rhs->shortName;
			lhs->skinFar = rhs->skinFar;
			lhs->defaultOutfit = rhs->defaultOutfit;
			lhs->sleepOutfit = rhs->sleepOutfit;
			lhs->unk144 = rhs->unk144;
			lhs->faction = rhs->faction;
			lhs->headparts = (BGSHeadPart**)FormHeap_Allocate(rhs->numHeadParts * sizeof(BGSHeadPart *));

			for (UInt32 i = 0; i < rhs->numHeadParts; ++i)
			{
				lhs->headparts[i] = rhs->headparts[i];
			}

			lhs->numHeadParts = rhs->numHeadParts;
			lhs->unk151 = rhs->unk151;
			lhs->unk152 = rhs->unk152;
			lhs->unk153 = rhs->unk153;
			lhs->color = rhs->color;
			lhs->pad157 = rhs->pad157;
			lhs->unk158 = rhs->unk158;

			lhs->faceMorph = (TESNPC::FaceMorphs*)FormHeap_Allocate(sizeof(TESNPC::FaceMorphs));
			lhs->faceMorph->CopyFrom(*rhs->faceMorph);

			lhs->unk160 = rhs->unk160;
		}

		default:
			// unsupported
			break;
	}
}

UInt32 BGSListForm::GetSize()
{
	UInt32 totalSize = forms.count;
	if(addedForms) {
		totalSize += addedForms->count;
	}

	return totalSize;
}

bool BGSListForm::Visit(BGSListForm::Visitor & visitor)
{
	// Base Added Forms
	for(UInt32 i = 0; i < forms.count; i++)
	{
		TESForm* childForm = NULL;
		if(forms.GetNthItem(i, childForm))
		{
			if(visitor.Accept(childForm))
				return true;
		}
	}

	// Script Added Forms
	if(addedForms) {
		for(int i = 0; i < addedForms->count; i++) {
			UInt32 formid = 0;
			addedForms->GetNthItem(i, formid);
			TESForm* childForm = LookupFormByID(formid);
			if(childForm) {
				if(visitor.Accept(childForm))
					return true;
			}
		}
	}

	return false;
}