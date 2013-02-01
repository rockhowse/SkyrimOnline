#pragma once

namespace Skyrim
{
	namespace Game
	{
		class Character
		{
		public:

			Vector3 GetPosition();
			Vector3 GetRotation();
			float GetHeading();

			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void SetHeading(float heading);
			void SetName(const std::string& pName);
			void SetFaceMorph(const std::vector<float>& faceMorphs);
			void SetFacePresets(const std::vector<uint32_t>& facePresets);
			void EquipItems(const std::vector<uint32_t>& items);

			uint32_t GetLocationId();
			const std::string& GetName();
			uint32_t GetRace();
			uint32_t GetGender();
			const std::vector<float>& GetFaceMorph();
			const std::vector<uint32_t>& GetFacePresets();
			const std::vector<uint32_t>& GetAllWornForms();

		private:

			std::string mName;
			Vector3 mPosition;
			Vector3 mRotation;
			uint32_t mRegion;
			uint32_t mRace;
			uint32_t mGender;
			std::vector<float> mFaceMorphs;
			std::vector<uint32_t> mPresets;
			std::vector<uint32_t> mWornForms;

		};
	}
}