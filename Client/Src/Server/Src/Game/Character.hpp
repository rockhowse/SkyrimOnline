#pragma once

#include "Object.hpp"

namespace Skyrim
{
	namespace Game
	{
		class Character : public Object
		{
		public:

			static void Register(class ScriptEngine* engine);

			void SetFaceMorph(const std::vector<float>& faceMorphs);
			void SetFacePresets(const std::vector<uint32_t>& facePresets);
			void EquipItems(const std::vector<uint32_t>& items);

			uint32_t GetLocationId();
			uint32_t GetRace();
			uint32_t GetGender();

			const std::vector<float>& GetFaceMorph();
			const std::vector<uint32_t>& GetFacePresets();
			const std::vector<uint32_t>& GetAllWornForms();

		private:

			uint32_t mRegion;
			uint32_t mRace;
			uint32_t mGender;
			std::vector<float> mFaceMorphs;
			std::vector<uint32_t> mPresets;
			std::vector<uint32_t> mWornForms;

		};
	}
}