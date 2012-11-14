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
		:mMode(true),
		 mPlayerCharacter(nullptr)
	{
		_trace
		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetAddress("127.0.0.1");
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&GameWorld::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&GameWorld::ConstructPlayer));
		TheMassiveMessageMgr->BeginMultiplayer(false);

		SetUser(EasySteam::Interface::GetInstance()->GetUser()->GetPersonaName());
	}
	//--------------------------------------------------------------------------------
	GameWorld::~GameWorld()
	{
		_trace
	}
	//--------------------------------------------------------------------------------
	unsigned int GameWorld::GetRendering()
	{
		return mRendering;
	}
	//--------------------------------------------------------------------------------
	std::string GameWorld::GetUser()
	{
		return mUsername;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnConnect(bool pStatus)
	{
		_trace
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnConnectionLost()
	{
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
		mRun = true;
		while (mRun)
		{
			System::Log::Flush();

			SetRendering(clock());
			uint32_t delta = uint32_t(mTimer.elapsed() * 1000);
			mTimer.restart();

			TheMassiveMessageMgr->Update();
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetRendering(unsigned int rendering)
	{
		mRendering = rendering;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::Setup()
	{
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetUser(const std::string& user)
	{
		mUsername = user;
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