#pragma once

#include <Game/PlayerGOMEntry.h>
#include <Logic/GameState.hpp>
#include <Game/TimeManager.hpp>
#include <Game/WeatherManager.hpp>

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

		Game::TimeManager& GetTimeManager();
		Game::WeatherManager& GetWeatherManager();

		static ::Game::Player* ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server);
		static std::vector<::Game::IGOMServer*> ConstructGOMServers(void*);

	private:

		//< Alright now start initializing gameplay stuff
		Game::TimeManager mTimeManager;
		Game::WeatherManager mWeatherManager;

		//< Common shit
		boost::timer mTimer;

		//< Game states
		boost::shared_ptr<Logic::GameState> mCurrentState;
		std::map<std::string, boost::shared_ptr<Logic::GameState>> mStates;

	};

	extern GameWorld* TheGameWorld;
}