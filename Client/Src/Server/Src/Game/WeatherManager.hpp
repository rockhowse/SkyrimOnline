#pragma once

namespace Skyrim
{
	namespace Game
	{
		class WeatherManager
		{
		public:

			static void Register(class ScriptEngine* engine);

			WeatherManager();

			void Update(float pDelta);
			
			uint32_t GetId();
			void SetWeather(uint32_t pWeather);

		private:

			uint32_t mWeather;

		};
	}
}