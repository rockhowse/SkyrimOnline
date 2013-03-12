#include "stdafx.h"
#include "GameWorld.h"
#include <Overlay/Message.h>

#include <Logic/Session.h>
#include <Logic/States/InGame.hpp>
#include <Logic/States/ShardList.hpp>
#include <Game/PlayerGOMServer.h>

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	GameWorld* TheGameWorld = nullptr;
	//--------------------------------------------------------------------------------
	GameWorld::GameWorld()
		:mMode(true),
		 mPlayerCharacter(FreeScript::Game::GetPlayer())
	{
		_trace
		Overlay::TheSystem = new Overlay::System;
		Overlay::TheMessage = Overlay::TheSystem->Instantiate<Overlay::Message>();
		Overlay::TheMessage->Hide();

		InputHook::GetInstance()->SetListener(this);
		Overlay::TheSystem->Acquire();

		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetVersion(kProtocolVersion);
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&GameWorld::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&GameWorld::ConstructPlayer));

		SetUser(EasySteam::Interface::GetInstance()->GetUser()->GetPersonaName());
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
	boost::shared_ptr<Logic::GameState> GameWorld::GetCurrentGameState()
	{
		return mCurrentState;
	}
	//--------------------------------------------------------------------------------
	FreeScript::Character& GameWorld::GetPlayerCharacter()
	{
		return mPlayerCharacter;
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
	void GameWorld::OnError(const std::string& pError)
	{
		System::Log::Debug(pError);
		System::Log::Flush();
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		if(!mMode)
		{
			boost::mutex::scoped_lock _(mInputGuard);
			mX = x;
			mY = y;
			mZ = z;
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnMousePress(BYTE code)
	{
		//if(!mMode)
		{
			boost::mutex::scoped_lock _(mInputGuard);
			ButtonEvent e = {code, true, true};
			mButtons.push_back(e);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnMouseRelease(BYTE code)
	{
		//if(!mMode)
		{
			boost::mutex::scoped_lock _(mInputGuard);
			ButtonEvent e = {code, true, false};
			mButtons.push_back(e);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnPress(BYTE code)
	{
		//if(!mMode)
		{
			boost::mutex::scoped_lock _(mInputGuard);
			ButtonEvent e = {code, false, true};
			mButtons.push_back(e);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::OnRelease(BYTE code)
	{
		//if(!mMode)
		{
			boost::mutex::scoped_lock _(mInputGuard);
			ButtonEvent e = {code, false, false};
			mButtons.push_back(e);
		}
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

			{
				boost::mutex::scoped_lock _(mInputGuard);
				Overlay::TheSystem->MouseMove(mX,mY,mZ);
				for(auto itor = mButtons.begin(), end = mButtons.end(); itor != end; ++itor)
				{
					if(itor->mouse)
					{
						if(!mMode)
							Overlay::TheSystem->InjectMouse(itor->key,itor->pressed);
					}
					else
					{
						if(mCurrentState && mCurrentState->IsSwitchingAllowed())
						{
							if(itor->key == DIK_F3 && itor->pressed == false)
							{
								SwitchMode();
							}
						}
						if(!mMode)
							Overlay::TheSystem->Inject(itor->key, itor->pressed);
					}
				}
				mButtons.clear();
			}
			

			TheMassiveMessageMgr->Update();
			if(mCurrentState)
				mCurrentState->OnUpdate(delta);
		}
	}
	//--------------------------------------------------------------------------------
	void GameWorld::SetMode(bool pMode)
	{
		mMode = pMode;
		if(mMode)
		{
			// In game mode -> enable controls
			FreeScript::Game::EnablePlayerControls(true,true,true,true,true,true,true,true,1);
			FreeScript::Game::SetInChargen(false, false, true);
			Overlay::TheSystem->SetCursor(false);
		}
		else
		{
			// In UI mode -> disable controls
			FreeScript::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
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
		gomServers.push_back(new Game::PlayerGOMServer);
		return gomServers;
	}
	//--------------------------------------------------------------------------------
}