#include "stdafx.h"
#include "GameForms.h"

Game::Oblivion::TESForm::TESForm(void * ptr)
	: Game::Oblivion::BaseFormComponent(ptr)
{

}

Game::Oblivion::TESForm::~TESForm()
{

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