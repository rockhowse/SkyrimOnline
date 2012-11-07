#include "stdafx.h"
#include "SkyrimOnline.h"
#include <Overlay/Message.h>

#include <Logic/Session.h>
#include <Logic/States/InGame.hpp>
#include <Logic/States/Login.hpp>
#include <Logic/States/ShardList.hpp>

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	SkyrimOnline* SkyrimOnline::instance = nullptr;
	//--------------------------------------------------------------------------------
	SkyrimOnline::SkyrimOnline()
		:mUI(Overlay::Interface::GetInstance()),mMode(true)
	{
		_trace

		InputHook::GetInstance()->SetListener(this);
		mUI->Acquire();

		Crypt::RSA::Init();
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->SetGOMServerConstructor(::Game::GameServer::GOMServerConstructor(&SkyrimOnline::ConstructGOMServers));
		TheMassiveMessageMgr->SetPlayerConstructor(::Game::GameServer::PlayerConstructor(&SkyrimOnline::ConstructPlayer));

		SetUser(EasySteam::Interface::GetInstance().GetUser()->GetPersonaName());
	}
	//--------------------------------------------------------------------------------
	SkyrimOnline::~SkyrimOnline()
	{
		_trace

		mUI->Reset();
	}
	//--------------------------------------------------------------------------------
	bool SkyrimOnline::Exists()
	{
		return instance != nullptr;
	}
	//--------------------------------------------------------------------------------
	Game::AssetManager& SkyrimOnline::GetAssetManager()
	{
		return mAssets;
	}
	//--------------------------------------------------------------------------------
	Game::ControllerManager& SkyrimOnline::GetControllerManager()
	{
		return mManager;
	}
	//--------------------------------------------------------------------------------
	boost::shared_ptr<Logic::GameState> SkyrimOnline::GetCurrentGameState()
	{
		return mCurrentState;
	}
	//--------------------------------------------------------------------------------
	SkyrimOnline& SkyrimOnline::GetInstance()
	{
		if(instance == nullptr)
			instance = new SkyrimOnline;
		return *instance;
	}
	//--------------------------------------------------------------------------------
	Overlay::Interface& SkyrimOnline::GetInterface()
	{
		return *mUI;
	}
	//--------------------------------------------------------------------------------
	Game::PlayerEntry& SkyrimOnline::GetPlayerEntry()
	{
		return mPlayer;
	}
	//--------------------------------------------------------------------------------
	unsigned int SkyrimOnline::GetRendering()
	{
		return mRendering;
	}
	//--------------------------------------------------------------------------------
	TimeManager& SkyrimOnline::GetTimeManager()
	{
		return mTimeManager;
	}
	//--------------------------------------------------------------------------------
	std::string SkyrimOnline::GetUser()
	{
		return mUsername;
	}
	//--------------------------------------------------------------------------------
	WeatherManager& SkyrimOnline::GetWeatherManager()
	{
		return mWeatherManager;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Kill()
	{
		delete instance;
		instance = nullptr;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnConnect(bool pStatus)
	{
		_trace
		if(pStatus)
		{
			mUI->GetMessage()->SetCaption("Negotiating connection with World !");
		}
		else
		{
			mUI->GetMessage()->SetCaption("The world is unreachable !");
		}
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnConnectionLost()
	{
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnError(const std::string& pError)
	{
		System::Log::Debug(pError);
		System::Log::Flush();
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		if(!mMode)
			mUI->MouseMove(x,y,z);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnMousePress(BYTE code)
	{
		if(!mMode)
			mUI->InjectMouse(code,true);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnMouseRelease(BYTE code)
	{
		if(!mMode)
			mUI->InjectMouse(code,false);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnPress(BYTE code)
	{
		if(!mMode)
			mUI->Inject(code,true);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnRelease(BYTE code)
	{
		if(!mMode)
			mUI->Inject(code,false);
		if(mCurrentState && mCurrentState->IsSwitchingAllowed())
		{
			if(code == DIK_F3)
			{
				SwitchMode();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnShardPick(const std::string& pAddress)
	{
		mUI->GetMessage()->SetCaption("Connecting to the World !");
		mUI->GetMessage()->Show();

		TheMassiveMessageMgr->SetAddress("127.0.0.1");
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->BeginMultiplayer(false);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnHost()
	{
		TheMassiveMessageMgr->SetPort(kGamePort);
		TheMassiveMessageMgr->BeginMultiplayer(true);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Run()
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
	void SkyrimOnline::SetMode(bool pMode)
	{
		mMode = pMode;
		if(mMode)
		{
			// In game mode -> enable controls
			//::Game::EnablePlayerControls(true,true,true,true,true,true,true,true,1);
			//::Game::SetInChargen(false, false, true);
			mUI->SetCursor(false);
		}
		else
		{
			// In UI mode -> disable controls
			//::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
			mUI->SetCursor(true);
		}

		InputHook::GetInstance()->SetInputEnabled(mMode);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetRendering(unsigned int rendering)
	{
		mRendering = rendering;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetState(const std::string& pState)
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
	void SkyrimOnline::Setup()
	{
		mStates["ShardList"].reset(new Logic::State::ShardList);
		mStates["InGame"].reset(new Logic::State::InGame);

		SetState("ShardList");
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetUser(const std::string& user)
	{
		mUsername = user;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Stop()
	{
		if(instance)
			instance->mRun = false;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SwitchMode()
	{
		_trace
		SetMode(!mMode);
	}
	//--------------------------------------------------------------------------------
	::Game::Player* SkyrimOnline::ConstructPlayer(::Game::Player::KeyType id, ::Game::GameServer* server)
	{
		return new Logic::Session(id, server);
	}
	//--------------------------------------------------------------------------------
	std::vector<::Game::IGOMServer*> SkyrimOnline::ConstructGOMServers(void*)
	{
		std::vector<::Game::IGOMServer*> gomServers;

		return gomServers;
	}
	//--------------------------------------------------------------------------------
}