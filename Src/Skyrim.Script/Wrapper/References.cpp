#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/References.hpp>
#include "common/skyscript.h"
#pragma managed

#include "References.h"

using namespace System;

namespace SkyrimScript
{
	namespace Wrapper
	{
		TESObjectREFR::TESObjectREFR(void* ptr) : Wrapper::TESForm(ptr)
		{

		}

		TESObjectREFR::~TESObjectREFR()
		{

		}

		Wrapper::TESForm^ TESObjectREFR::BaseForm::get()
		{
			return gcnew Wrapper::TESForm(((FreeScript::TESObjectREFR*)ptr)->baseForm);
		}

		Actor::Actor(void* ptr) : Wrapper::TESObjectREFR(ptr)
		{

		}

		Actor::~Actor()
		{

		}
	}
}