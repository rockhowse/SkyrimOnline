#include <Logic/ChatJail.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		ChatJail::ChatJail()
			:mBurst(0), mJailTime(0), mLastMessage(0), mAccumulator(0)
		{
		}
		//---------------------------------------------------------------------
		ChatJail::~ChatJail()
		{

		}
		//---------------------------------------------------------------------
		void ChatJail::Update(uint32_t pDelta)
		{
			mAccumulator += pDelta;
			mJailTime -= pDelta;
		}
		//---------------------------------------------------------------------
		bool ChatJail::CanSend()
		{
			if(mAccumulator - mLastMessage < 1000)
			{
				++mBurst;
			}
			else
				mBurst = 0;

			mLastMessage = mAccumulator;

			if(mBurst > 5)
			{
				mBurst = 0;
				mJailTime = 5000;
			}

			if(mJailTime > 0)
			{
				return false;
			}

			return true;
		}
		//---------------------------------------------------------------------
	}
}