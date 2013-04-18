#pragma once

#include "Components.h"

namespace Skyrim
{
	namespace Script
	{
		public ref class TESForm : public Script::BaseFormComponent
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

		public ref class TESObjectCELL : public Script::TESForm
		{
		public:

			TESObjectCELL(void* ptr);
			~TESObjectCELL();

		};

		public ref class TESObject : public Script::TESForm
		{
		public:

			TESObject(void* ptr);
			~TESObject();
		};

		public ref class TESBoundObject : public TESObject
		{
		public:

			TESBoundObject(void* ptr);
			~TESBoundObject();
		};

		public ref class TESBoundAnimObject : public TESBoundObject
		{
		public:

			TESBoundAnimObject(void* ptr);
			~TESBoundAnimObject();
		};

		public ref class TESActorBase : public TESBoundAnimObject
		{
		public:

			TESActorBase(void* ptr);
			~TESActorBase();
		};

		public ref class TESNPC : public TESActorBase
		{
		public:

			TESNPC(void* ptr);
			~TESNPC();

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

		public ref class TESRace : public Script::TESForm
		{
		public:

			TESRace(void* ptr);
			~TESRace();

			
		};
	}
}