#pragma once

#include "Types.h"

namespace Skyrim
{
	namespace Script
	{
		public ref class BaseFormComponent
		{
		protected:

			void* ptr;

		public:

			BaseFormComponent(void* ptr);
			virtual ~BaseFormComponent();

			property void* NativeHandle
			{
				void* get();
			}
		};

		public ref class TESFullName : public Script::BaseFormComponent
		{
		public:

			TESFullName(void* ptr);
			~TESFullName();

			property Script::BSFixedString^ Name
			{
				Script::BSFixedString^ get();
			}
		};
	}
}