#pragma once

namespace Skyrim
{
	namespace Game
	{
		class SkyrimFormManager
		{
		public:

			static SkyrimFormManager* GetInstance();

			FreeScript::TESForm* GetForm(uint32_t pRace, uint32_t pGender);
			void ReleaseForm(FreeScript::TESForm* pForm);

		private:

			SkyrimFormManager();
			~SkyrimFormManager();

			bool mUsedOffsets[100];
			uint32_t mBaseAddr;

			static SkyrimFormManager* mInstance;
		};
	}
}