#include "stdafx.h"
#include "GameForms.h"

Game::Oblivion::TESForm::TESForm(void * ptr)
	: Game::Oblivion::BaseFormComponent(ptr)
{

}

Game::Oblivion::TESForm::~TESForm()
{

}

int Game::Oblivion::TESForm::FormID::get()
{
	int addr = (int)ptr;
	addr += 0xC;
	return *(int*)addr;
}

int Game::Oblivion::TESForm::FormType::get()
{
	int addr = (int)ptr;
	addr += 0x4;
	return *(unsigned char*)addr;
}

Game::Oblivion::BaseFormComponent::BaseFormComponent(void * ptr)
	:ptr(ptr)
{

}

Game::Oblivion::BaseFormComponent::~BaseFormComponent()
{

}

void* Game::Oblivion::BaseFormComponent::NativeHandle::get()
{
	return ptr;
}