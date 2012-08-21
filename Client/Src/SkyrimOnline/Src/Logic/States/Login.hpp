#pragma once

#include <Overlay/Login.h>
#include <Logic/GameState.hpp>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			class Login : public GameState
			{
			public:
				Login();
				virtual ~Login();

				void OnEnter();
				void OnLeave();
				void OnUpdate(uint32_t pDelta);

				bool IsSwitchingAllowed();

				uint32_t GetId()
				{
					return 'logi';
				}

				void Authenticate(const std::string& pUser, const std::string& pPass);
				void OnAuthenticationReply(std::string pData);

			private:

				boost::shared_ptr<Overlay::Login> mLogin;
			};
		}
	}
}