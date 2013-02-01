#include "stdafx.h"
#include <Game/PlayerGOMServer.h>

namespace Skyrim
{
	namespace Game
	{
		PlayerGOMServer::PlayerGOMServer()
		{
		}

		void PlayerGOMServer::DoAdd(WrappedType* model, int32 replicationState, int32 id /* = -1 */)
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

		void PlayerGOMServer::DoRemove(int32_t id, int32_t replicationState)
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
			if(id != TheMassiveMessageMgr->GetLocalPlayer()->GetKey())
			{
				if(state >= 0 && state < ::Game::ReplicationStateProperty::kCount)
				{
					auto itor = replicationMap[state].find(id);
					if(itor == replicationMap[state].end())
					{

						Framework::Network::Packet packet;
						packet.Initialize(serializedData);
						PlayerGOMTransaction transaction;
						packet >> transaction;

						if(transaction.IsSetName())
							cout << "Spawning player with name : " << (string)transaction.GetName() << endl;

						//boost::shared_ptr<ActorController> controller = boost::make_shared<ActorController>(race, gender);
						//mControllers[id] = controller;

						//Add(controller->GetCharacter().get(), state, id);
						itor = replicationMap[state].find(id);
					}

					//itor->second->Deserialize(serializedData);
				}
			}
		}
	}
}
