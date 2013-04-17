#include "Stdafx.h"
#include "Input.hpp"

using namespace System;
using namespace Skyrim::Script;

Event^ Input::Poll()
{
	if(_events->Count > 0)
	{
		Event^ e = _events->First->Value;
		_events->RemoveFirst();
		return e;
	}
	return nullptr;
}

void Input::Push(Event^ ev)
{
	_events->AddLast(ev);
}