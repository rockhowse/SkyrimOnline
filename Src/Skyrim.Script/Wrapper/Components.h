#pragma once

#include "Types.h"

namespace Game
{
	namespace Skyrim
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

		public ref class TESFullName : public Skyrim::BaseFormComponent
		{
		public:

			TESFullName(void* ptr);
			~TESFullName();

			property Skyrim::BSFixedString^ Name
			{
				Skyrim::BSFixedString^ get();
			}
		};
	}
}