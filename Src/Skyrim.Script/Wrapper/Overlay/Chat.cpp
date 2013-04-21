#include "Stdafx.h"
#include "Chat.h"
#include <Overlay/Chat.h>
#include <Overlay/System.h>

using namespace Skyrim::Script;

Overlay::Chat::Chat()
{
	ptr = new Skyrim::Overlay::Chat(Skyrim::Overlay::TheSystem->GetGui());
}

Overlay::Chat::~Chat()
{
	delete (Skyrim::Overlay::Chat*)ptr;
}

bool Overlay::Chat::Visible::get()
{
	if(ptr)
		return ((Skyrim::Overlay::Chat*)ptr)->IsVisible();
	return false;
}

void Overlay::Chat::Visible::set(bool pVisible)
{
	if(ptr)
		return ((Skyrim::Overlay::Chat*)ptr)->SetVisible(pVisible);
}