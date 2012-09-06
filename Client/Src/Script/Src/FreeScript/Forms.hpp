#pragma once

#include "Components.hpp"
#include "Types.hpp"

namespace FreeScript
{
	class TESObjectREFR;
	class TESForm : public ::FreeScript::BaseFormComponent
	{
	public:

		uint32_t pad00to04;
		uint32_t flags;	
		uint32_t formID;	
		uint16_t pad10to12;	
		uint8_t	formType;
		uint8_t	__alignement;
	};

	class TESObject : public ::FreeScript::TESForm
	{
	public:
	};

	class TESRace : public ::FreeScript::TESForm
	{
	public:

		char pad014to2bc[0x2bc - 0x14];
	};

	class TESRaceForm : public ::FreeScript::BaseFormComponent
	{
	public:
		::FreeScript::TESRace	* race;
	};

	class TESBoundObject : public ::FreeScript::TESObject
	{
	public:
		struct Bound
		{
			uint16_t	x;
			uint16_t	y;
			uint16_t	z;
		};

		Bound lower, upper;
	};

	class TESBoundAnimObject : public ::FreeScript::TESBoundObject
	{
	public:
	};

	class TESActorBase : public ::FreeScript::TESBoundAnimObject
	{
	public:
		char				pad00to84[0x84 - 0x20];
		TESFullName			fullName;
		char				pad8ctoc0[0xc0 - 0x8c];
	};

	class TESNPC : public ::FreeScript::TESActorBase
	{
	public:

		struct FaceMorphs
		{
			enum
			{
				OptionCount =	19,
				PresetCount =	4,
			};

			float	 option[OptionCount];
			uint32_t presets[PresetCount];
		};

		// parents
		::FreeScript::TESRaceForm		race;	
		char pad0c8to15c[0x15c - 0xc8];

		FaceMorphs	* faceMorph;
		char pad160to164[0x164 - 0x160];
	};

	class TESObjectCELL : public FreeScript::TESForm
	{
	public:

		FreeScript::TESFullName		fullName;

		char pad1cto4c[0x4c - 0x1c];
		FreeScript::Vector<FreeScript::TESObjectREFR*> childList;
		char pad58to8c[0x8c - 0x58];
	};

	class BGSLocation : public FreeScript::TESForm
	{
	public:

		FreeScript::TESFullName		fullName;

		char pad1cto88[0x88 - 0x1c];
	};

}