#include "stdafx.h"
#include "NetEngine.hpp"
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		NetEngine* NetEngine::mInstance = nullptr;

		NetEngine& NetEngine::GetInstance()
		{
			if(mInstance == nullptr)
				mInstance = new NetEngine;
			return *mInstance;
		}

		bool NetEngine::IsServer()
		{
			return GetInstance().mServerMode;
		}

		bool NetEngine::IsConnected()
		{
			if(GetInstance().mServerMode)
			{
				return false;
			}
			if(GetInstance().mClient && !GetInstance().mClient->IsOffline())
				return true;

			return false;
		}

		void NetEngine::Host()
		{
			GetInstance().mServerMode = true;
		}

		void NetEngine::Join(const std::string& pIp, const std::string& pPort)
		{
			auto& watcher = SkyrimOnline::GetInstance().GetPlayerWatcher();

			GetInstance().mServerMode = false;
			GetInstance().mClient = Session::Create();
			GetInstance().mClient->Connect(pIp, pPort);
			GetInstance().mClient->OnChatMessage.connect(boost::bind(&NetEngine::_OnChatMessage, &GetInstance(), _1));
			GetInstance().mClient->OnSpawn.connect(boost::bind(&NetEngine::_OnSpawn, &GetInstance()));

			GetInstance().mEventLinks.push_back(watcher.OnEnterWorld.connect(boost::bind(&NetEngine::SendCharacterInfo, &GetInstance(), _1)));
			GetInstance().mEventLinks.push_back(watcher.OnMove      .connect(boost::bind(&NetEngine::SendMoveAndLook,   &GetInstance(), _1, _2)));
			GetInstance().mEventLinks.push_back(watcher.OnMount     .connect(boost::bind(&NetEngine::SendMount,         &GetInstance(), _1)));
			GetInstance().mEventLinks.push_back(watcher.OnUnmount   .connect(boost::bind(&NetEngine::SendUnmount,       &GetInstance())));
			GetInstance().mEventLinks.push_back(watcher.OnRegion    .connect(boost::bind(&NetEngine::SendEnterRegion,   &GetInstance(), _1)));
		}

		void NetEngine::Update(float pDelta)
		{
			if(mServerMode);
			else if(mClient)
				mClient->Update(pDelta);
		}

		Session::pointer NetEngine::GetClient()
		{
			return mClient;
		}

		void NetEngine::Write(Network::Packet& pPacket)
		{
			if(mServerMode);
			else if(mClient)
				mClient->Write(pPacket);
		}

		void NetEngine::_OnSpawn()
		{
			OnSpawn();
		}

		void NetEngine::_OnChatMessage(const std::string& pMessage)
		{
			OnChatMessage(pMessage);
		}
	}
}