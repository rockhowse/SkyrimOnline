#include "Stdafx.h"
#include "System.h"
#include <Overlay/System.h>

using namespace Game;

void Overlay::System::InjectKeyboardKey(unsigned char key, bool pressed)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->Inject(key, pressed);
}

void Overlay::System::InjectMouseKey(unsigned char key, bool pressed)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->InjectMouse(key, pressed);
}

void Overlay::System::InjectMousePosition(unsigned int x, unsigned int y, unsigned int z)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->MouseMove(x, y, z);
}

bool Overlay::System::CursorVisible::get()
{
	if(Skyrim::Overlay::TheSystem)
		return Skyrim::Overlay::TheSystem->IsCursorVisible();
	return false;
}

void Overlay::System::CursorVisible::set(bool pVisible)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->SetCursor(pVisible);
}

void Overlay::System::Register(Game::IUpdatable^ u)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->Register((::IUpdatable*)u->NativeHandle);
}

void Overlay::System::Unregister(Game::IUpdatable^ u)
{
	if(Skyrim::Overlay::TheSystem)
		Skyrim::Overlay::TheSystem->Unregister((::IUpdatable*)u->NativeHandle);
}

Overlay::System::System()
{

}