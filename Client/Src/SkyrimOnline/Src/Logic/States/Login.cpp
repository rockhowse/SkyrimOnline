#include <stdafx.h>
#include <Logic/States/Login.hpp>
#include <GameWorld.h>
#include <Overlay/Message.h>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			//--------------------------------------------------------------------------------
			Login::Login()
			{
				mLogin = boost::make_shared<Overlay::Login>(Overlay::TheSystem->GetGui());
				mLogin->OnLogin.connect([this](std::string u, std::string p){this->Authenticate(u,p);});
			}
			//--------------------------------------------------------------------------------
			Login::~Login()
			{

			}
			//--------------------------------------------------------------------------------
			void Login::OnEnter()
			{
				TheGameWorld->SetMode(false);
				FreeScript::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
				FreeScript::Game::SetInChargen(true, true, false);
				Overlay::TheSystem->SetCursor(true);
				mLogin->Show();
			}
			//--------------------------------------------------------------------------------
			void Login::OnLeave()
			{
				mLogin->Hide();
			}
			//--------------------------------------------------------------------------------
			void Login::OnUpdate(uint32_t pDelta)
			{
			}
			//--------------------------------------------------------------------------------
			bool Login::IsSwitchingAllowed()
			{
				return false;
			}
			//--------------------------------------------------------------------------------
			void Login::Authenticate(const std::string& user, const std::string& pass)
			{
				TheGameWorld->SetUser(user);
				Overlay::TheMessage->Show();
				mLogin->Hide();

				Overlay::TheMessage->SetCaption("Connecting...");
				std::ostringstream os;
				os << "/authentication.php?do=login&username=" << Network::UrlEncode(user) << "&pass=" << Network::UrlEncode(pass);

				System::Log::Debug(user + std::string(" | ") + pass);
			}
			//--------------------------------------------------------------------------------
			void Login::OnAuthenticationReply(std::string pData)
			{
				if(pData[0] == '1')
				{
					TheGameWorld->SetState("ShardList");
				}
				else
				{
					Overlay::TheMessage->SetCaption("Authentication failed !\nMessage : " + pData);
					mLogin->Show();
				}
			}
			//--------------------------------------------------------------------------------
		}
	}
}