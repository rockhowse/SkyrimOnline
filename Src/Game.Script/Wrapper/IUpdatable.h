#pragma once
#pragma managed
#include <Engine/Data.hpp>

namespace Game
{
	public ref class IUpdatable
	{
	public:

		void* NativeHandle;
	};
}