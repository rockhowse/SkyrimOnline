#pragma once
#pragma managed
#include <Engine/Data.hpp>

namespace Skyrim
{
	namespace Script
	{
		public ref class IUpdatable
		{
		public:

			void* NativeHandle;
		};
	}
}