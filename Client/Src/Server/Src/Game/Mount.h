#pragma once

#include <Bullet/btBulletCollisionCommon.h>
#include <boost/make_shared.hpp>

namespace Skyrim
{
	namespace Network
	{
		class Session;
	}
	namespace Game
	{
		class Mount
		{
		public:

			Mount(unsigned int pSkyrimID);

			unsigned int GetSkyrimId();

		private:

			friend class Network::Session;

			btVector3 mPosition, mRotation;
			unsigned int mSkyrimID;
		};
	}
}