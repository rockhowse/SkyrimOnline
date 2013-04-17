#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Forms.h"

using namespace System;

using namespace Skyrim;

Script::TESForm::TESForm(void* ptr) : Script::BaseFormComponent(ptr)
{

}
Script::TESForm::~TESForm()
{

}

int Script::TESForm::FormID::get()
{
	return ((FreeScript::TESForm*)ptr)->formID;
}

int Script::TESForm::FormType::get()
{
	return ((FreeScript::TESForm*)ptr)->formType;
}

int Script::TESForm::Flags::get()
{
	return ((FreeScript::TESForm*)ptr)->flags;
}

Script::TESObjectCELL::TESObjectCELL(void* ptr) : Script::TESForm(ptr)
{

}

Script::TESObjectCELL::~TESObjectCELL()
{

}

