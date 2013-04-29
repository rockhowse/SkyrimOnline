#pragma once

#include "../GameForms.hpp"

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

		public ref class TESForm : public Oblivion::BaseFormComponent, ITESForm
		{
		public:

			TESForm(void * ptr);
			~TESForm();

			virtual property int FormID 
			{
				int get();
			}

			virtual property int FormType
			{
				int get();
			}
		};

	}
}