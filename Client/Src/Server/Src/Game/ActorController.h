#pragma once

#include "Character.hpp"

namespace Skyrim
{
	namespace Game
	{
		class ActorController
		{
		public:

			ActorController(unsigned int pRace, uint32_t pSex);
			~ActorController();

			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);

			void InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, uint32_t time);
			void SetMount(unsigned int pMount);

			boost::shared_ptr<Character> GetCharacter();

		private:

			struct InterpolationPoint
			{
				float posX, posY, posZ;
				float rotX, rotY, rotZ;
				float elapsed;
			};

			InterpolationPoint mPoint;
			bool mInit;
			boost::shared_ptr<Character> mMe;
			uint32_t mMount;
		};
	}
}