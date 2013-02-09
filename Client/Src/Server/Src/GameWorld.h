#pragma once

#include <Game/PlayerGOMEntry.h>
#include <Logic/GameState.hpp>
#include <Game/WorldManager.h>

namespace Skyrim
{
	class GameWorld
	{
	public:

		GameWorld();
		~GameWorld();

		void Setup();

		void Run();

		// Network event
		void OnError(const std::string&);

		Game::WorldManager& GetWorldManager();

		static ::Game::Player* ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server);
		static std::vector<::Game::IGOMServer*> ConstructGOMServers(void*);

	private:

		//< Alright now start initializing gameplay stuff
		Game::WorldManager mWorldMgr;

		//< Common shit
		boost::timer mTimer;

	};

	extern GameWorld* TheGameWorld;
}