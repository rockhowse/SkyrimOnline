#include <stdafx.h>

namespace GameModule
{
	namespace Engine
	{
		namespace Interfaces
		{
			class IController
			{
				public:

				virtual void EnableInput() = 0;
				virtual void DisableInput() = 0;;
			};
		}
	}
}