#pragma once

#include "Types.h"

namespace Skyrim
{
	namespace Script
	{
		namespace Wrapper
		{
			public ref class BaseFormComponent
			{
			protected:

				void* ptr;

			public:

				BaseFormComponent(void* ptr);
				virtual ~BaseFormComponent();
			};

			public ref class TESFullName : public Wrapper::BaseFormComponent
			{
			public:

				TESFullName(void* ptr);
				~TESFullName();

				property Wrapper::BSFixedString^ Name
				{
					Wrapper::BSFixedString^ get();
				}
			};
		}
	}
}