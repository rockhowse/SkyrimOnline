#pragma once

#include <Game/Character.h>
#include <Game/PlayerWatcher.h>
#include <Logic/Session.h>

namespace Skyrim
{
	namespace Logic
	{
		class NetEngine
		{
		public:

			static NetEngine& GetInstance();
			static bool IsServer();
			static bool IsConnected();
			static void Host();
			static void Join(const std::string& pIp, const std::string& pPort);

			void Update(float pDelta);
			
			void SendEnterRegion(uint32_t pRegion);
			void SendCharacterInfo(Game::Character& pCharacter);
			void SendMoveAndLook(Game::Character& pCharacter, uint32_t pDelta);
			void SendMount(uint32_t pId);
			void SendUnmount();
			void SendChatMessage(const std::string& pMessage);

			boost::signal<void(const std::string&)> OnChatMessage;
			boost::signal<void()>					OnSpawn;

			Session::pointer GetClient();

			void _OnChatMessage(const std::string& pMessage);
			void _OnSpawn();

		protected:

			void Write(Network::Packet& pPacket);

		private:

			bool mServerMode;

			Session::pointer mClient;
			//Session::pointer server;

			std::vector<boost::signals::connection> mEventLinks;

			static NetEngine* mInstance;
		};
	}
}