#include "stdafx.h"
#include "Session.h"
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/System.h>
#include <GameWorld.h>
#include <Network/IoServicePool.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::Init()
		{
			::Game::Player::Register(kServerChatMessage, &Session::HandleChatMessage);
			::Game::Player::Register(kServerServiceResponse, &Session::HandleServiceResponse);
			::Game::Player::Register(kServerMount, &Session::HandleMount);
			::Game::Player::Register(kServerUnmount, &Session::HandleUnmount);
		}
		//--------------------------------------------------------------------------------
		Session::Session(unsigned int id, ::Game::GameServer* server) : ::Game::Player(id, server) 
		{
		}
		//--------------------------------------------------------------------------------
		Session::~Session()
		{
			try{
				std::for_each(mEventLinks.begin(), mEventLinks.end(), [](boost::signals::connection& pConnection)
				{
					pConnection.disconnect();
				});

				_trace
			}
			catch(...)
			{
				System::Log::Debug("Session::~Session() error");
			}
		}
		//--------------------------------------------------------------------------------
	}
}