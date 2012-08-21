#pragma once

#include "Character.h"

namespace Skyrim
{
	namespace Game
	{
		class RemotePlayer
		{
		public:

			RemotePlayer(unsigned int pId, unsigned int pRace, uint32_t pSex);
			~RemotePlayer();

			void Update(uint32_t elapsed);
			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, uint32_t time);
			void SetMount(unsigned int pMount);

			boost::shared_ptr<Character> GetCharacter();
			unsigned int GetId();

		private:

			struct InterpolationPoint
			{
				float posX, posY, posZ;
				float rotX, rotY, rotZ;
				float elapsed;
			};

			InterpolationPoint mPrevious, mNext;
			bool mInit;
			unsigned int mId;
			CActor*	mMaster;
			boost::shared_ptr<Character> mMe;
			boost::shared_ptr<Character> mMount;
		};
	}
}