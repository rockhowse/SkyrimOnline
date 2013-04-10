#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Forms.h"

using namespace System;

namespace SkyrimScript
{
	namespace Wrapper
	{
		TESForm::TESForm(void* ptr) : BaseFormComponent(ptr)
		{

		}

		TESForm::~TESForm()
		{

		}

		int TESForm::FormID::get()
		{
			return ((FreeScript::TESForm*)ptr)->formID;
		}

		int TESForm::FormType::get()
		{
			return ((FreeScript::TESForm*)ptr)->formType;
		}

		int TESForm::Flags::get()
		{
			return ((FreeScript::TESForm*)ptr)->flags;
		}

		TESObjectCELL::TESObjectCELL(void* ptr) : Wrapper::TESForm(ptr)
		{

		}

		TESObjectCELL::~TESObjectCELL()
		{

		}
	}
}