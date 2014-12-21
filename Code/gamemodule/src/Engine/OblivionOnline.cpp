#include <Engine\OblivionOnline.h>

namespace GameModule
{
	namespace Engine
	{
		OblivionOnline::OblivionOnline()
		{
			auto OblivionOnlineDll = GetModuleHandleA("OblivionOnline.dll");

			setPlayerControls = (tSetPlayerControls)GetProcAddress(OblivionOnlineDll, "SetPlayerControls");
		}

		void OblivionOnline::SetPlayerControls()
		{
			setPlayerControls();
		}
	}
}