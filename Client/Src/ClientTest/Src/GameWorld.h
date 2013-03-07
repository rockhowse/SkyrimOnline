#pragma once

#include <Game/PlayerGOMEntry.h>
#include <Game/AssetManager.h>


namespace Skyrim
{
	class GameWorld
	{
	public:

		GameWorld();
		~GameWorld();

		void Setup();

		void Run();

		// End Input events

		// Network event
		void OnConnectionLost();
		void OnConnect(bool);
		void OnError(const std::string&);

		unsigned int GetRendering();
		void SetRendering(unsigned int);

		std::string		GetUser();
		void			SetUser(const std::string& user);	

		static ::Game::Player* ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server);
		static std::vector<::Game::IGOMServer*> ConstructGOMServers(void*);

	private:

		bool mMode;
		bool mRun;
		uint32_t mRendering;

		//< Alright now start initializing gameplay stuff
		FreeScript::TimeManager mTimeManager;
		FreeScript::WeatherManager mWeatherManager;
		Game::AssetManager mAssets;

		//< Data
		std::string mUsername;
		FreeScript::Character mPlayerCharacter;

		//< Common shit
		boost::timer mTimer;
	};

	extern GameWorld* TheGameWorld;
}