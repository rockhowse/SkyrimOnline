#pragma once

using namespace System;

namespace Game
{
	namespace Oblivion
	{
		public ref class BaseFormComponent
		{
		protected:

			void* ptr;

		public:

			BaseFormComponent(void * ptr);
			~BaseFormComponent();

			property void* NativeHandle
			{
				void* get();
			}
		};

		public ref class TESForm : public Oblivion::BaseFormComponent
		{
		public:

			TESForm(void * ptr);
			~TESForm();
		};

	}
}