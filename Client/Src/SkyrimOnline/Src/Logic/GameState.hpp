#pragma once

namespace Skyrim
{
	namespace Logic
	{
		class GameState
		{
		public:
			GameState(){}
			virtual ~GameState(){}

			virtual void OnEnter() = 0;
			virtual void OnLeave() = 0;
			virtual void OnUpdate(uint32_t pDelta) = 0;
			virtual uint32_t GetId() = 0;

			virtual bool IsSwitchingAllowed() = 0;
		};
	}
}