#pragma once

#include <Game/Character.h>
#include <Game/PlayerWatcher.h>

using boost::asio::ip::tcp;

namespace Skyrim
{
	using namespace Framework::Network;

	namespace Logic
	{
		class Session 
			: public boost::enable_shared_from_this<Session>,
			public Network::NinjatoStrategy
		{
		public:

			typedef boost::shared_ptr<Session> pointer;

			Session(Game::PlayerWatcher& pPlayer);
			~Session();

			void Write(Network::Packet& msg);
			void Update(float pDelta);

			static void Init();
			static pointer Create(Game::PlayerWatcher& pPlayer)
			{
				return pointer(new Session(pPlayer));
			}

			bool IsOffline();

			/**
			 * Sets the cipher
			 * @param pCipher The cipher to use
			 */
			void SetCipher(Crypt::Cipher* pCipher);

			void Connect(const std::string& pAddress, const std::string& pPort);

			void SendEnterRegion(uint32_t pRegion);
			void SendCharacterInfo(Game::Character& pCharacter);
			void SendMoveAndLook(Game::Character& pCharacter, uint32_t pDelta);
			void SendMount(uint32_t pId);
			void SendUnmount();
			void SendChatMessage(const std::string& pMessage);

			boost::signal<void(const std::string&)> OnChatMessage;
			boost::signal<void()>					OnSpawn;

		protected:

			void HandlePlayerSpawn(Network::Packet&);
			void HandlePlayerMoveAndLook(Network::Packet&);
			void HandlePlayerRemove(Network::Packet&);
			void HandleChatMessage(Network::Packet&);
			void HandleServiceResponse(Network::Packet&);
			void HandleMount(Network::Packet&);
			void HandleUnmount(Network::Packet&);

		private:

			typedef  void(Session::*CallBack)(Network::Packet&);

		private:

			Network::TcpConnection::pointer mConnection;
			std::vector<boost::signals::connection> mEventLinks;

			static std::unordered_map<unsigned int, CallBack> mHandlers;
		};
	}
}