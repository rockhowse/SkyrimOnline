#include "stdafx.h"
#include "GameWorld.h"

#include <Logic/Session.h>
#include <Game/PlayerGOMServer.h>

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	GameWorld* TheGameWorld = nullptr;
	//--------------------------------------------------------------------------------
	GameWorld::GameWorld()
	{
		_trace

		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&GameWorld::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&GameWorld::ConstructPlayer));
	}
	//--------------------------------------------------------------------------------
	GameWorld::~GameWorld()
	{
		_trace
	}
	//--------------------------------------------------------------------------------
	Game::TimeManager& GameWorld::GetTimeManager()
	{
		return mTimeManager;
	}
	//--------------------------------------------------------------------------------
	Game::WeatherManager& GameWorld::GetWeatherManager()
	{
		return mWeatherManager;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnError(const std::string& pError)
	{
		System::Log::Debug(pError);
		System::Log::Flush();
	}
	//--------------------------------------------------------------------------------
	void GameWorld::Run()
	{
		while (1)
		{
			System::Log::Flush();

			uint32_t delta = uint32_t(mTimer.elapsed() * 1000);
			mTimer.restart();			

			TheMassiveMessageMgr->Update();
			if(mCurrentState)
				mCurrentState->OnUpdate(delta);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::Setup()
	{
	}
	//--------------------------------------------------------------------------------
	::Game::Player* GameWorld::ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server)
	{
		return new Logic::Session(id, server);
	}
	//--------------------------------------------------------------------------------
	std::vector<::Game::IGOMServer*> GameWorld::ConstructGOMServers(void*)
	{
		std::vector<::Game::IGOMServer*> gomServers;
		gomServers.push_back(new Game::PlayerGOMServer);
		return gomServers;
	}
	//--------------------------------------------------------------------------------
}