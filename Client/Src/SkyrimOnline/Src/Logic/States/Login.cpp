#include <stdafx.h>
#include <Logic/States/Login.hpp>
#include <SkyrimOnline.h>
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
				mLogin = boost::make_shared<Overlay::Login>(SkyrimOnline::GetInstance().GetInterface().GetGui());
				mLogin->OnLogin.connect([this](std::string u, std::string p){this->Authenticate(u,p);});
			}
			//--------------------------------------------------------------------------------
			Login::~Login()
			{

			}
			//--------------------------------------------------------------------------------
			void Login::OnEnter()
			{
				SkyrimOnline::GetInstance().SetMode(false);
				::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
				::Game::SetInChargen(true, true, false);
				SkyrimOnline::GetInstance().GetInterface().SetCursor(true);
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
				SkyrimOnline::GetInstance().SetUser(user);
				SkyrimOnline::GetInstance().GetInterface().GetMessage()->Show();
				mLogin->Hide();

				SkyrimOnline::GetInstance().GetInterface().GetMessage()->SetCaption("Connecting...");
				std::ostringstream os;
				os << "/authentication.php?do=login&username=" << Network::UrlEncode(user) << "&pass=" << Network::UrlEncode(pass);

				System::Log::Debug(user + std::string(" | ") + pass);
			}
			//--------------------------------------------------------------------------------
			void Login::OnAuthenticationReply(std::string pData)
			{
				if(pData[0] == '1')
				{
					SkyrimOnline::GetInstance().SetState("ShardList");
				}
				else
				{
					SkyrimOnline::GetInstance().GetInterface().GetMessage()->SetCaption("Authentication failed !\nMessage : " + pData);
					mLogin->Show();
				}
			}
			//--------------------------------------------------------------------------------
		}
	}
}