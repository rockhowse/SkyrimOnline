#pragma once

namespace Skyrim
{
	namespace Game
	{
		class SkyrimFormManager
		{
		public:

			static SkyrimFormManager* GetInstance();

			TESForm* GetForm(uint32_t pRace, uint32_t pGender);
			void ReleaseForm(TESForm* pForm);

		private:

			SkyrimFormManager();
			~SkyrimFormManager();

			std::list<uint32_t> mUsed;
			uint32_t mBaseAddr;

			static SkyrimFormManager* mInstance;
		};
	}
}