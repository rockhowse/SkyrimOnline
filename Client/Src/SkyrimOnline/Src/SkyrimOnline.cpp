#include "stdafx.h"
#include "SkyrimOnline.h"
#include <Overlay/Message.h>
#include <Data/NpcList.h>

#include <Logic/States/InGame.hpp>
#include <Logic/States/Login.hpp>
#include <Logic/States/ShardList.hpp>

namespace Skyrim
{
	//--------------------------------------------------------------------------------
	SkyrimOnline* SkyrimOnline::instance = nullptr;
	//--------------------------------------------------------------------------------
	SkyrimOnline::SkyrimOnline()
		:mUI(Overlay::Interface::GetInstance()), mInput(*this),mMode(true),mIoPool(1)
	{
		System::Log::Debug("Mod()");
		
		unsigned int count = SkyrimScript::ActorListCount();
		std::ostringstream os;
		os << "Count : " << count;
		System::Log::Debug(os.str());
		for(unsigned int i = 0; i < count; ++i)
		{
			std::ostringstream os;
			os << "Ref : " << Form::GetFormID((TESForm*)SkyrimScript::ActorListAt(i));
			System::Log::Debug(os.str());
		}

		mUI->Acquire();

		Crypt::RSA::Init();
		Logic::Session::Init(); // Init callbacks

		mIoPool.Run();

		System::Log::Debug("Mod() -e");
	}
	//--------------------------------------------------------------------------------
	SkyrimOnline::~SkyrimOnline()
	{
		System::Log::Debug("~Mod()");
		mUI->Reset();
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Setup()
	{
		mStates["Login"].reset(new Logic::State::Login);
		mStates["ShardList"].reset(new Logic::State::ShardList);
		mStates["InGame"].reset(new Logic::State::InGame);

		SetState("Login");
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Run()
	{
		mRun = true;
		while (mRun)
		{
			System::Log::Flush();

			SetRendering(clock());
			uint32_t delta = uint32_t(mTimer.elapsed() * 1000);
			mTimer.restart();

			mInput.Update();
			
			if(mCurrentState)
				mCurrentState->OnUpdate(delta);

			Wait(0);
		}
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SwitchMode()
	{
		System::Log::Debug("SwitchMode()");
		SetMode(!mMode);
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetMode(bool pMode)
	{
		mMode = pMode;
		if(mMode)
		{
			// In game mode -> enable controls
			::Game::EnablePlayerControls(true,true,true,true,true,true,true,true,1);
			::Game::SetInChargen(false, false, true);
			mUI->SetCursor(false);
		}
		else
		{
			// In UI mode -> disable controls
			::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
			mUI->SetCursor(true);
		}
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
	boost::shared_ptr<Logic::GameState> SkyrimOnline::GetCurrentGameState()
	{
		return mCurrentState;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnConnectionLost()
	{
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnShardPick(const std::string& pAddress)
	{
		mUI->GetMessage()->SetCaption("Connecting to the World !");
		mUI->GetMessage()->Show();

		mSession = Logic::Session::Create(mPlayer);

		mSession->Connect(pAddress, "27500");
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnConnect(bool pStatus)
	{
		if(pStatus)
		{
			mUI->GetMessage()->SetCaption("Negotiating connection with World !");
			std::string decKey = Skyrim::SkyrimOnline::RandomData(32);
			std::string encKey = Skyrim::SkyrimOnline::RandomData(32);
			std::string decIV = Skyrim::SkyrimOnline::RandomData(8);
			std::string encIV = Skyrim::SkyrimOnline::RandomData(8);

			Network::Packet packet(1, 0, Opcode::CMSG_HANDSHAKE);
			packet << mUsername << decKey << encKey << decIV << encIV;

			mSession->SetCipher(new Crypt::Cipher(encKey, decKey, encIV, decIV));

			mSession->Write(packet);

			mUI->GetMessage()->Hide();

			SetState("InGame");
		}
		else
		{
			mUI->GetMessage()->SetCaption("The world is unreachable !");
		}
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::OnError(const std::string& pError)
	{
		System::Log::Debug(pError);
		System::Log::Flush();
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
			else if(code == DIK_F6)
			{
			}
		}
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
	void SkyrimOnline::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		if(!mMode)
			mUI->MouseMove(x,y,z);
	}
	//--------------------------------------------------------------------------------
	SkyrimOnline& SkyrimOnline::GetInstance()
	{
		if(instance == nullptr)
			instance = new SkyrimOnline;
		return *instance;
	}
	//--------------------------------------------------------------------------------
	bool SkyrimOnline::Exists()
	{
		return instance != nullptr;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Kill()
	{
		delete instance;
		instance = nullptr;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::Stop()
	{
		if(instance)
			instance->mRun = false;
	}
	//--------------------------------------------------------------------------------
	Game::CharacterManager& SkyrimOnline::GetCharacterManager()
	{
		return mManager;
	}
	//--------------------------------------------------------------------------------
	Logic::Session::pointer SkyrimOnline::GetSession()
	{
		return mSession;
	}
	//--------------------------------------------------------------------------------
	Overlay::Interface& SkyrimOnline::GetInterface()
	{
		return *mUI;
	}
	//--------------------------------------------------------------------------------
	Game::TimeManager& SkyrimOnline::GetTimeManager()
	{
		return mTimeManager;
	}
	//--------------------------------------------------------------------------------
	Game::WeatherManager& SkyrimOnline::GetWeatherManager()
	{
		return mWeatherManager;
	}
	//--------------------------------------------------------------------------------
	Game::AssetManager& SkyrimOnline::GetAssetManager()
	{
		return mAssets;
	}
	//--------------------------------------------------------------------------------
	Game::PlayerWatcher& SkyrimOnline::GetPlayerWatcher()
	{
		return mPlayer;
	}
	//--------------------------------------------------------------------------------
	Network::IoServicePool& SkyrimOnline::GetIoPool()
	{
		return mIoPool;
	}
	//--------------------------------------------------------------------------------
	unsigned int SkyrimOnline::GetRendering()
	{
		return mRendering;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetRendering(unsigned int rendering)
	{
		mRendering = rendering;
	}
	//--------------------------------------------------------------------------------
	std::string SkyrimOnline::GetUser()
	{
		return mUsername;
	}
	//--------------------------------------------------------------------------------
	void SkyrimOnline::SetUser(const std::string& user)
	{
		mUsername = user;
	}
	//--------------------------------------------------------------------------------
	std::string SkyrimOnline::RandomData(uint32_t pSize)
	{
		std::string output;

		std::normal_distribution<long double> distribution;
		std::mt19937 engine(time(0));

		while(output.size() < pSize)
		{
			std::string data;
			CryptoPP::MD5 hash;

			byte digest[ CryptoPP::MD5::DIGESTSIZE ];
			std::string message = std::to_string(distribution(engine));

			hash.CalculateDigest( digest, (const byte*)message.data(), message.length() );
			CryptoPP::HexEncoder encoder;

			encoder.Attach( new CryptoPP::StringSink( data ) );
			encoder.Put( digest, sizeof(digest) );
			encoder.MessageEnd();

			output += data;
		}
		return output.substr(0, pSize);
	}
	//--------------------------------------------------------------------------------
}