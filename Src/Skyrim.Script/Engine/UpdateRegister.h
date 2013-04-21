#pragma once

#include <list>
#include "IUpdatable.hpp"

struct UpdateRegister
{

	void Update();
	void Register(IUpdatable* u);
	void Unregister(IUpdatable* u);

private:

	std::list<IUpdatable*> mUpdatables;
};