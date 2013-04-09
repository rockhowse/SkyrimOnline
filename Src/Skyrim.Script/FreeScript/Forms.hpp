#pragma once

#include "Components.hpp"
#include "Types.hpp"

namespace FreeScript
{
	class TESObjectREFR;
	class BGSColorForm;

	class TESForm : public BaseFormComponent
	{
	public:

		virtual void			Unk_04();
		virtual void			Unk_05();
		virtual void			Unk_06();
		virtual void			Unk_07();
		virtual void			Unk_08();
		virtual void			Unk_09();
		virtual void			Unk_0A();
		virtual void			Unk_0B();
		virtual void			Unk_0C();
		virtual void			Unk_0D();
		virtual void			Unk_0E();
		virtual void			Unk_0F();
		virtual void			Unk_10();
		virtual void			Unk_11();
		virtual void			Unk_12();
		virtual void			Unk_13();
		virtual void			Unk_14();
		virtual void			Unk_15();
		virtual void			Unk_16();
		virtual void			Unk_17();
		virtual void			Unk_18();
		virtual void			Unk_19();
		virtual void			Unk_1A();
		virtual void			Unk_1B();
		virtual void			Unk_1C();
		virtual void			Unk_1D();
		virtual void			Unk_1E();
		virtual void			Unk_1F();
		virtual void			Unk_20();
		virtual void			Unk_21();
		virtual void			Unk_22();
		virtual void			Unk_23();
		virtual void			Unk_24();
		virtual void			Unk_25();
		virtual void			Unk_26();
		virtual void			Unk_27();
		virtual void			Unk_28();
		virtual void			Unk_29();
		virtual void			Unk_2A();
		virtual void			Unk_2B();
		virtual void			Unk_2C();
		virtual void			CopyFrom(TESForm *);

		uint32_t pad00to04;
		uint32_t flags;	
		uint32_t formID;	
		uint16_t pad10to12;	
		uint8_t	formType;
		uint8_t	__alignement;
	};

	class TESObject : public TESForm
	{
	public:
	};

	class TESRace : public TESForm
	{
	public:

		enum Race
		{
			Argorian = 13740,
			Breton,
			Dunmer,
			Altmer,
			Imperial,
			Khajiit,
			Nord,
			Orc,
			Redguard,
			Bosmer
		};

		char pad014to2bc[0x2bc - 0x14];
	};

	class TESWeather : public TESForm
	{

	};

	class TESGlobal : public TESForm
	{

	};

	class TESRaceForm : public BaseFormComponent
	{
	public:
		::FreeScript::TESRace	* race;
	};

	class TESBoundObject : public TESObject
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

	class TESBoundAnimObject : public TESBoundObject
	{
	public:
	};

	class TESActorBase : public TESBoundAnimObject
	{
	public:
		char				pad00to84[0x84 - 0x20];
		TESFullName			fullName;
		char				pad8ctoc0[0xc0 - 0x8c];
	};

	class TESNPC : public TESActorBase
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

		struct HeadContainer
		{
			BGSColorForm* color;
			void* unk;
		};

		// parents
		::FreeScript::TESRaceForm		race;	
		char pad0c8to10c[0x10c - 0xc8];
		void*							tesClass;
		HeadContainer*					head;

		char pad114to154[0x154 - 0x114];
		uint8_t r, g, b; // 154
		char pad157to15c[0x15c - 0x157];

		FaceMorphs	* faceMorph;
		char pad160to164[0x164 - 0x160];
	};

	class TESObjectCELL : public TESForm
	{
	public:

		FreeScript::TESFullName		fullName;

		char pad1cto4c[0x4c - 0x1c];
		FreeScript::Vector<FreeScript::TESObjectREFR*> childList;
		char pad58to8c[0x8c - 0x58];
	};

	class BGSLocation : public TESForm
	{
	public:

		FreeScript::TESFullName		fullName;

		char pad1cto88[0x88 - 0x1c];
	};

	class BGSColorForm : public TESForm
	{
	public:

		TESFullName fullName;

		uint32_t color;
		uint32_t pad;
	};

}