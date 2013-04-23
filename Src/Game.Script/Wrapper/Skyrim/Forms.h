#pragma once

#include "Components.h"

using namespace System;

namespace Game
{
	namespace Skyrim
	{
		public ref class TESForm : public Skyrim::BaseFormComponent
		{
		public:

			TESForm(void* ptr);
			~TESForm();

			property int FormID
			{
				int get();
			}

			property int FormType
			{
				int get();
			}

			property int Flags
			{
				int get();
			}
		};

		public ref class TESObjectCELL : public Skyrim::TESForm
		{
		public:

			TESObjectCELL(void* ptr);
			~TESObjectCELL();

		};

		public ref class TESObject : public Skyrim::TESForm
		{
		public:

			TESObject(void* ptr);
			~TESObject();
		};

		public ref class TESBoundObject : public Skyrim::TESObject
		{
		public:

			TESBoundObject(void* ptr);
			~TESBoundObject();
		};

		public ref class TESBoundAnimObject : public Skyrim::TESBoundObject
		{
		public:

			TESBoundAnimObject(void* ptr);
			~TESBoundAnimObject();
		};

		public ref class TESActorBase : public Skyrim::TESBoundAnimObject
		{
		public:

			TESActorBase(void* ptr);
			~TESActorBase();
		};

		public enum class RaceIds
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

		public ref class TESRace : public Skyrim::TESForm
		{
		public:

			TESRace(void* ptr);
			~TESRace();
		};

		public ref class TESNPC : public Skyrim::TESActorBase
		{
		public:

			TESNPC(void* ptr);
			~TESNPC();

			property Skyrim::TESRace^ Race
			{
				Skyrim::TESRace^ get();
			}

			property System::UInt32 Gender
			{
				System::UInt32 get();
			}

			property array<float>^ FaceMorphs
			{
				array<float>^ get();
				void set(array<float>^ val);
			}

		};		
	}
}