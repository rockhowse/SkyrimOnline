#pragma once

namespace Game
{
	namespace Script
	{
		namespace Skyrim
		{
			public ref class Globals
			{
			public:

				static void SetScale(float pValue);
				static void SetHour(float pValue);
				static void SetDay(float pValue);
				static void SetMonth(float pValue);
				static void SetYear(float pValue);

			};
		}
	}
}