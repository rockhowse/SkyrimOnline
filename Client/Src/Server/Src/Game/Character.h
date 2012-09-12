#pragma once

#include <stdint.h>

#include <vector>

#include <Bullet/btBulletCollisionCommon.h>
#include <boost/shared_ptr.hpp>

namespace Skyrim
{
	namespace Logic
	{
		class Session;
	}
	namespace Game
	{
		class Party;
		class Mount;
		/**
		* Character class
		*/
		class Character
		{
		public:

			Character();
			~Character();

			/**
			* Allows the player to create a party.
			*/
			void CreateParty();

			// Appearance
			uint32_t GetRace();
			uint32_t GetLevel();
			uint32_t GetGender();
			const std::vector<float>&		GetFaceMorph();
			const std::vector<uint32_t>&	GetWornForms();


			bool HasMount();
			boost::shared_ptr<Mount> GetMount();
			/**
			* Sets the player's mount.
			* @param pMountID Id of the mount to spawn.
			*/
			void SetMount(unsigned int pMountID);

			/**
			* Allows the player to invite another player to his current party.
			* @param pSession
			*/
			void InvitePlayer(boost::shared_ptr<Logic::Session> pSession);

		private:

			friend class Logic::Session;

			boost::shared_ptr<Party> mParty;

			boost::shared_ptr<Mount> mMount;
			btVector3 Position, Rotation;

			// Appearance
			uint32_t mRace, mLevel, mGender;
			std::vector<float> mFaceMorph;
			std::vector<uint32_t> mWornForms;

			uint32_t mElapsed;
		};
	}
}