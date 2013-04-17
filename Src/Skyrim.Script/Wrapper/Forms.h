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
	}
}