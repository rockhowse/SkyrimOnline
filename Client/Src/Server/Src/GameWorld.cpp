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
		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetVersion(kProtocolVersion);
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&GameWorld::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&GameWorld::ConstructPlayer));

		std::ostringstream os;
		os << "Hosting server with protocol version " << kProtocolVersion << " on port " << kGamePort << endl;
		Framework::System::Log::Print(os.str());

		TheMassiveMessageMgr->BeginMultiplayer(true);		
	}
	//--------------------------------------------------------------------------------
	GameWorld::~GameWorld()
	{
		_trace
	}
	//--------------------------------------------------------------------------------
	Game::WorldManager& GameWorld::GetWorldManager()
	{
		return mWorldMgr;
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

			mWorldMgr.Update(delta);
			TheMassiveMessageMgr->Update();

			boost::this_thread::yield();
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