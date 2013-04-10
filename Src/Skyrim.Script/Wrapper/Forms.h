#pragma once

#include "Components.h"

namespace SkyrimScript
{
	namespace Wrapper
	{
		public ref class TESForm : public Wrapper::BaseFormComponent
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

		public ref class TESObjectCELL : public Wrapper::TESForm
		{
		public:

			TESObjectCELL(void* ptr);
			~TESObjectCELL();

		};
	}
}