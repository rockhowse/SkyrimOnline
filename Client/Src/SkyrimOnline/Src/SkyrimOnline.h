#pragma once

#include <Game/PlayerEntry.h>
#include <Game/ControllerManager.h>
#include <Game/AssetManager.h>

#include <Overlay/Interface.h>
#include <Engine/InputManager.h>
#include <Logic/GameState.hpp>

namespace Skyrim
{
	class SkyrimOnline
		: public InputListener
	{
	public:

		SkyrimOnline();
		~SkyrimOnline();

		void Setup();

		void Run();

		// Input events
		void OnPress(BYTE code);
		void OnRelease(BYTE code);
		void OnMousePress(BYTE code);
		void OnMouseRelease(BYTE code);
		void OnMouseMove(unsigned int x, unsigned int y, unsigned int z);
		// End Input events

		// Network event
		void OnConnectionLost();
		void OnConnect(bool);
		void OnError(const std::string&);

		// UI events
		void OnShardPick(const std::string& pAddress);
		void OnHost();

		// Singleton
		static SkyrimOnline& GetInstance();
		static void Kill();
		static bool Exists();
		static void Stop();
		// End Singleton

		Game::ControllerManager& GetControllerManager();
		Overlay::Interface& GetInterface();
		TimeManager& GetTimeManager();
		WeatherManager& GetWeatherManager();
		Game::AssetManager& GetAssetManager();
		Game::PlayerEntry& GetPlayerEntry();

		unsigned int GetRendering();
		void SetRendering(unsigned int);

		std::string		GetUser();
		void			SetUser(const std::string& user);	

		void SwitchMode();
		void SetMode(bool pMode);
		void SetState(const std::string& pState);

		boost::shared_ptr<Logic::GameState> GetCurrentGameState();

		static ::Game::Player* ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server);
		static std::vector<::Game::IGOMServer*> ConstructGOMServers(void*);

	private:

		//< Note order is important, gui first !
		Overlay::Interface* mUI;

		bool mMode;
		bool mRun;
		uint32_t mRendering;

		//< Alright now start initializing gameplay stuff
		Game::PlayerEntry mPlayer;
		Game::ControllerManager mManager;
		TimeManager mTimeManager;
		WeatherManager mWeatherManager;
		Game::AssetManager mAssets;

		//< Data
		std::string mUsername;

		//< Common shit
		boost::timer mTimer;

		//< Game states
		boost::shared_ptr<Logic::GameState> mCurrentState;
		std::map<std::string, boost::shared_ptr<Logic::GameState>> mStates;

		static SkyrimOnline* instance;
	};
}