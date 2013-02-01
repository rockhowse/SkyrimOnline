#include "stdafx.h"
#include <Game/PlayerGOMServer.h>

namespace Skyrim
{
	namespace Game
	{
		PlayerGOMServer::PlayerGOMServer()
		{
		}

		void PlayerGOMServer::DoAdd(WrappedType* model, int32_t replicationState, int32_t id /* = -1 */)
		{
			if(id == -1)
			{
				id = (++replicationId);
			}
			if(replicationState >= 0 && replicationState < ::Game::ReplicationStateProperty::kCount)
			{
				if(replicationMap[replicationState].find(id) == replicationMap[replicationState].end())
				{
					auto entry = std::make_shared<PlayerGOMEntry>(model);
					entry->SetKey(id);
					replicationMap[replicationState].insert(std::make_pair(id, entry));
				}
			}
		}

		void PlayerGOMServer::_Add(boost::shared_ptr<ActorController> ctrlr, int32_t replicationState, int32_t id /* = -1 */)
		{
			if(id == -1)
			{
				id = (++replicationId);
			}
			if(replicationState >= 0 && replicationState < ::Game::ReplicationStateProperty::kCount)
			{
				if(replicationMap[replicationState].find(id) == replicationMap[replicationState].end())
				{
					// THIS IS REALLY IMPORTANT
					newIds.insert(id);

					mControllers[id] = ctrlr;
					auto entry = std::make_shared<PlayerGOMEntry>(ctrlr->GetCharacter().get());
					entry->SetKey(id);
					replicationMap[replicationState].insert(std::make_pair(id, entry));
				}
			}
		}

		void PlayerGOMServer::DoRemove(int32_t replicationState, int32_t id)
		{
			if(replicationState >= 0 && replicationState < ::Game::ReplicationStateProperty::kCount)
			{
				auto itor = replicationMap[replicationState].find(id);
				if(itor != replicationMap[replicationState].end())
				{
					replicationMap[replicationState].erase(itor);
				}

				auto itor2 = mControllers.find(id);
				if(itor2 != mControllers.end())
				{
					mControllers.erase(itor2);
				}
			}
		}

		void PlayerGOMServer::DoUpdate()
		{

		}

		void PlayerGOMServer::UpdateEntry(int32_t id, int32_t state, const std::string& serializedData)
		{
			// UNREACHABLE

			//assert(false);
		}
	}
}
