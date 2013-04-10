#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Forms.h"

using namespace System;

using namespace Skyrim::Script;

Wrapper::TESForm::TESForm(void* ptr) : BaseFormComponent(ptr)
{

}

Wrapper::TESForm::~TESForm()
{

}

int Wrapper::TESForm::FormID::get()
{
	return ((FreeScript::TESForm*)ptr)->formID;
}

int Wrapper::TESForm::FormType::get()
{
	return ((FreeScript::TESForm*)ptr)->formType;
}

int Wrapper::TESForm::Flags::get()
{
	return ((FreeScript::TESForm*)ptr)->flags;
}

Wrapper::TESObjectCELL::TESObjectCELL(void* ptr) : Wrapper::TESForm(ptr)
{

}

Wrapper::TESObjectCELL::~TESObjectCELL()
{

}

