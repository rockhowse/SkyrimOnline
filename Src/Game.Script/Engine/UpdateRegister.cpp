#include "Stdafx.h"
#include "UpdateRegister.h"

void UpdateRegister::Update()
{
	for(auto u : mUpdatables)
		u->Update();
}

void UpdateRegister::Register(IUpdatable* u)
{
	mUpdatables.push_back(u);
}

void UpdateRegister::Unregister(IUpdatable* u)
{
	mUpdatables.remove(u);
}