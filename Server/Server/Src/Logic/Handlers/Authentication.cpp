#include <Logic/Session.h>
#include <Logic/World.h>
#include <DAO/Account.h>
#include <Crypt/RSA.h>
#include <System/Tools.h>

using namespace Framework;

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandleHandshake(Framework::Network::Packet& pPacket)
		{
			uint32_t version, flag;

			pPacket >> version >> flag;

			std::string rsaData;

			rsaData = Crypt::RSA::Decrypt(pPacket.GetBuffer());
			pPacket.Initialize(rsaData);
			pPacket >> mAccount.User;
			mAccount.Nicename = mAccount.User;

			if(mAccount.Id == 0)
			{
				/*auto dao = DAO::Load(mAccount);
				dao->OnEvent.connect(boost::bind(&Session::HandleUserLoad, shared_from_this(), _1, _2));
				mWorld->GetDatabaseWorkQueue()->Push(dao);*/
				HandleUserLoad(DAO::IDAO::LOAD, true);
			}

			std::string salsaEnc, salsaDec, salsaEncIV, salsaDecIV;
			pPacket >> salsaEnc >> salsaDec >> salsaEncIV >> salsaDecIV;

			mCipher.reset(new Crypt::Cipher(salsaEnc, salsaDec, salsaEncIV, salsaDecIV));
			mConnection->Start();

			SendChatMessage("Press F3 to use the chat !");
			SendServiceTimesource(12.f, 1.f, 1.f);
		}
		//---------------------------------------------------------------------
		void Session::HandleRequestClose(Framework::Network::Packet& pPacket)
		{
			//mConnection->Close();
		}
		//---------------------------------------------------------------------
		void Session::HandleUserLoad(DAO::IDAO::Type pType, bool pSuccess)
		{
			//if(mAccount.Id != 0)
			{
			}
			//else
			{
			//	mConnection->Close();
			}
		}
		//---------------------------------------------------------------------
	}
}