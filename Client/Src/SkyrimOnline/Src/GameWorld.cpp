#include "stdafx.h"
#include "GameWorld.h"
#include <Overlay/Message.h>

#include <Logic/Session.h>
#include <Logic/States/InGame.hpp>
#include <Logic/States/Login.hpp>
#include <Logic/States/ShardList.hpp>

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	GameWorld* TheGameWorld = nullptr;
	//--------------------------------------------------------------------------------
	GameWorld::GameWorld()
		:mMode(true)
	{
		_trace
		Overlay::TheSystem = new Overlay::System;
		Overlay::TheMessage = Overlay::TheSystem->Instantiate<Overlay::Message>();

		InputHook::GetInstance()->SetListener(this);
		Overlay::TheSystem->Acquire();

		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&GameWorld::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&GameWorld::ConstructPlayer));

		SetUser(EasySteam::Interface::GetInstance().GetUser()->GetPersonaName());
	}
	//--------------------------------------------------------------------------------
	GameWorld::~GameWorld()
	{
		_trace

		Overlay::TheSystem->Reset();
	}
	//--------------------------------------------------------------------------------
	Game::AssetManager& GameWorld::GetAssetManager()
	{
		return mAssets;
	}
	//--------------------------------------------------------------------------------
	Game::ControllerManager& GameWorld::GetControllerManager()
	{
		return mManager;
	}
	//--------------------------------------------------------------------------------
	boost::shared_ptr<Logic::GameState> GameWorld::GetCurrentGameState()
	{
		return mCurrentState;
	}
	//--------------------------------------------------------------------------------
	unsigned int GameWorld::GetRendering()
	{
		return mRendering;
	}
	//--------------------------------------------------------------------------------
	TimeManager& GameWorld::GetTimeManager()
	{
		return mTimeManager;
	}
	//--------------------------------------------------------------------------------
	std::string GameWorld::GetUser()
	{
		return mUsername;
	}
	//--------------------------------------------------------------------------------
	WeatherManager& GameWorld::GetWeatherManager()
	{
		return mWeatherManager;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnConnect(bool pStatus)
	{
		_trace
		if(pStatus)
		{
			Overlay::TheMessage->SetCaption("Negotiating connection with World !");
		}
		else
		{
			Overlay::TheMessage->SetCaption("The world is unreachable !");
		}
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
	void GameWorld::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		if(!mMode)
			Overlay::TheSystem->MouseMove(x,y,z);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnMousePress(BYTE code)
	{
		if(!mMode)
			Overlay::TheSystem->InjectMouse(code,true);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnMouseRelease(BYTE code)
	{
		if(!mMode)
			Overlay::TheSystem->InjectMouse(code,false);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnPress(BYTE code)
	{
		if(!mMode)
			Overlay::TheSystem->Inject(code,true);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnRelease(BYTE code)
	{
		if(!mMode)
			Overlay::TheSystem->Inject(code,false);
		if(mCurrentState && mCurrentState->IsSwitchingAllowed())
		{
			if(code == DIK_F3)
			{
				SwitchMode();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnShardPick(const std::string& pAddress)
	{
		Overlay::TheMessage->SetCaption("Connecting to the World !");
		Overlay::TheMessage->Show();

		TheMassiveMessageMgr->SetAddress("127.0.0.1");
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->BeginMultiplayer(false);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnHost()
	{
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->BeginMultiplayer(true);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::Run()
	{
		mRun = true;
		while (mRun)
		{
			System::Log::Flush();

			EasySteam::Interface::Run();

			SetRendering(clock());
			uint32_t delta = uint32_t(mTimer.elapsed() * 1000);
			mTimer.restart();

			TheMassiveMessageMgr->Update();
			if(mCurrentState)
				mCurrentState->OnUpdate(delta);

			Wait(0);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetMode(bool pMode)
	{
		mMode = pMode;
		if(mMode)
		{
			// In game mode -> enable controls
			//::Game::EnablePlayerControls(true,true,true,true,true,true,true,true,1);
			//::Game::SetInChargen(false, false, true);
			Overlay::TheSystem->SetCursor(false);
		}
		else
		{
			// In UI mode -> disable controls
			//::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
			Overlay::TheSystem->SetCursor(true);
		}

		InputHook::GetInstance()->SetInputEnabled(mMode);
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetRendering(unsigned int rendering)
	{
		mRendering = rendering;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetState(const std::string& pState)
	{
		if(mCurrentState)
			mCurrentState->OnLeave();

		if(mStates[pState])
		{
			mCurrentState = mStates[pState];
			mCurrentState->OnEnter();
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::Setup()
	{
		mStates["ShardList"].reset(new Logic::State::ShardList);
		mStates["InGame"].reset(new Logic::State::InGame);

		SetState("ShardList");
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetUser(const std::string& user)
	{
		mUsername = user;
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SwitchMode()
	{
		_trace
		SetMode(!mMode);
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

		return gomServers;
	}
	//--------------------------------------------------------------------------------
}