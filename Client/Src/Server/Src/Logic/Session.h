#pragma once

#include <Entity/Account.h>
#include <Network/Packet.h>
#include <Crypt/Cipher.h>
#include <Network/TcpConnection.h>
#include <Network/NinjatoStrategy.h>
#include <Game/Character.h>
#include <DAO/DAO.h>

#include <Logic/ChatJail.h>

#include <boost/asio.hpp>
#include <boost/timer.hpp>
#include <boost/tuple/tuple.hpp>

#include <deque>
#include <unordered_map>

namespace Skyrim
{
	namespace Logic
	{
		using namespace Framework::Network;
		// Forward declaration
		class World;

		/**
		 * @class Session
		 * @brief Handles a single client as a session
		 */
		class Session :
			private boost::noncopyable, public boost::enable_shared_from_this<Session>, public Framework::Network::NinjatoStrategy
		{
		public:

			typedef boost::shared_ptr<Session> pointer;

			Session(Framework::Network::TcpConnection::pointer pConnection, World* pWorld, uint32_t mId);
			virtual ~Session();

			/**
			 * Starts listening to the session
			 */
			void Start();
			/**
			 * Parse packets, run logic...
			 */
			void Update(uint32_t pElapsed);
			/**
			 * Set up the opcode handlers, must be called once
			 */
			static void Setup();
			/**
			 * Get the session's id
			 * @return The id
			 */
			unsigned int GetId();

			std::string GetName();
			/**
			 * Write a packet to the session
			 * @param pPacket The packet to write
			 */
			void Write(Framework::Network::Packet& pPacket);

			float GetDistance(Session::pointer pPlayer);

			/// Senders
			void SendIntroduceConnection	();
			void SendClientInformation		();
			void SendServiceResponse		(const std::string& pSignature);
			void SendCharacterEnterRegion	(uint32_t pId);
			void SendSpawnPlayer			(Session::pointer pPlayer);
			void SendMount					(Session::pointer pPlayer);
			void SendUnmount				(Session::pointer pPlayer);
			void SendMoveAndLook			(Session::pointer pPlayer);
			void SendRemove					(Session::pointer pPlayer);
			void SendChatMessage			(const std::string& pMessage);
			void SendServiceTimesource		(float pHour, float pDay, float pMonth);
			/// End Senders

			/// Gameplay callbacks
			void HandlePlayerEvent(Session::pointer pPlayer);
			/// End gameplay callbacks

		protected:

			/// Handlers
				// General
			void HandlePing(Framework::Network::Packet& pPacket);
			void HandleBlackHole(Framework::Network::Packet& pPacket);
			void HandleChatMessage(Framework::Network::Packet& pPacket);
				// Authentication
			void HandleHandshake(Framework::Network::Packet& pPacket);
			void HandleRequestClose(Framework::Network::Packet& pPacket);
				// Service
			void HandleServiceRequest(Framework::Network::Packet& pPacket);
			void HandleServiceAck(Framework::Network::Packet& pPacket);
				// Characters
			void HandleUnmount(Framework::Network::Packet& pPacket);
			void HandleMount(Framework::Network::Packet& pPacket);
			void HandleCharacterInfo(Framework::Network::Packet& pPacket);
			void HandlePositionAndLook(Framework::Network::Packet& pPacket);
			void HandleEnterRegion(Framework::Network::Packet& pPacket);
			/// End Handlers

			/// Database callbacks
			void HandleUserLoad(Framework::DAO::IDAO::Type pType, bool pSuccess);
			/// End database callbacks

		private:

			void Broadcast(Framework::Network::Packet& pPacket);

			typedef  void(Session::*CallBack)(Framework::Network::Packet&);
			Game::Character& GetCharacter();
			Framework::Network::TcpConnection::pointer mConnection;

			World*							mWorld;

			uint32_t						mRegion;
			Entity::Account					mAccount;
			Game::Character					mCharacter;
			ChatJail						mChatJail;
			uint32_t						mId;

			// static handlers
			static std::unordered_map<uint32_t, CallBack> mHandlers;
		};
	}
}