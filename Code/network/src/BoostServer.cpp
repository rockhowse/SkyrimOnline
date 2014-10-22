#include "BoostServer.h"
#include "BoostManager.h"
#include "BoostConnection.h"
#include "BoostAcceptor.h"
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

BoostServer::BoostServer()
	: m_lightTaskManager(4)
	, m_mediumTaskManager(4)
	, m_heavyTaskManager(4)
	, m_ipv4Acceptor(0)
	, m_ipv6Acceptor(0)
	, m_idPool(65535)
{
}

BoostServer::~BoostServer()
{
    for(auto itor = m_idToConnection.begin(), end = m_idToConnection.end(); itor != end; ++itor)
    {
        itor->second->Close();
    }

    delete m_ipv4Acceptor;
    delete m_ipv6Acceptor;
}

bool BoostServer::Update()
{
	{
		boost::recursive_mutex::scoped_lock _(m_mapGuard);

		m_lightTaskManager.Gather();
		m_mediumTaskManager.Gather();
		m_heavyTaskManager.Gather();

		for (auto itor = m_idToConnection.begin(), end = m_idToConnection.end(); itor != end;)
		{
			BoostConnection* pConnection = itor->second;

			// If connection was lost and is not marked for delete, mark it for delete
			if (!pConnection->IsConnected() && !pConnection->IsMarkedForDelete())
			{
				// Notify user only if he was notified that the connection ever existed
				if (pConnection->IsEncrypted())
				{
					OnDisconnection(pConnection->GetId());
				}
				
				pConnection->MarkForDelete();
			}
			// If the connection is marked for delete and outstanding tasks are all done, delete and remove
			else if (pConnection->CanDelete())
			{
				delete pConnection;
				itor = m_idToConnection.erase(itor);
				continue;
			}
			// Or we are dealing with a live connection
			else
			{
				ReadBuffer* pBuffer = nullptr;
				while (pConnection->Consume(pBuffer))
				{
					if (pBuffer == nullptr)
					{
						OnConnection(pConnection->GetId());
					}
					else if (pConnection->IsEncrypted())
					{
						OnConsume(pConnection->GetId(), pBuffer);
					}

					delete pBuffer;
				}
			}
			++itor;
		}
	}
    
	OnUpdate();

    return true;
} 
BoostConnection* BoostServer::OnConnection(BoostConnection* apConnection)
{
    apConnection->Accept();
    
	m_mapGuard.lock();
    m_idToConnection[apConnection->GetId()] = apConnection;
	m_mapGuard.unlock();

    return new BoostConnection(BoostManager::GetInstance().GetIoService(), (uint16_t)m_idPool.GetId());
}

void BoostServer::Host(uint16_t aPort)
{
    delete m_ipv4Acceptor;
    delete m_ipv6Acceptor;

	m_ipv4Acceptor = new BoostAcceptor(aPort, this, NetIPv4(), BoostManager::GetInstance().GetIoService());
	m_ipv6Acceptor = new BoostAcceptor(aPort + 1, this, NetIPv6(), BoostManager::GetInstance().GetIoService());

	m_ipv4Acceptor->Accept(new BoostConnection(BoostManager::GetInstance().GetIoService(), (uint16_t)m_idPool.GetId()));
	m_ipv6Acceptor->Accept(new BoostConnection(BoostManager::GetInstance().GetIoService(), (uint16_t)m_idPool.GetId()));

	LOG(INFO) << "Started IPv4 listener on port " << aPort;
	LOG(INFO) << "Started IPv6 listener on port " << aPort + 1;
}

std::string BoostServer::Serialize(Packet* apMessage)
{
	WriteBuffer buffer;
	apMessage->Serialize(&buffer);

	uint32_t length = 0;
	std::string outBuffer;
	outBuffer.append((char*)&length, 4);

	outBuffer.append((char*)buffer.GetBuffer(), buffer.Size());

	*((uint32_t*)outBuffer.data()) = (uint32_t)outBuffer.size() - 4;

	return outBuffer;
}

std::string BoostServer::Serialize(WriteBuffer* apMessage)
{
	uint32_t length = 0;
	std::string outBuffer;
	outBuffer.append((char*)&length, 4);

	outBuffer.append((char*)apMessage->GetBuffer(), apMessage->Size());

	*((uint32_t*)outBuffer.data()) = (uint32_t)outBuffer.size() - 4;

	return outBuffer;
}

std::string BoostServer::Serialize(const std::string& aMessage)
{
	uint32_t length = 0;
	std::string outBuffer;
	outBuffer.append((char*)&length, 4);

	outBuffer.append((char*)aMessage.data(), aMessage.size());

	*((uint32_t*)outBuffer.data()) = (uint32_t)outBuffer.size() - 4;

	return outBuffer;
}

void BoostServer::Send(uint16_t aConnectionId, Packet* apMessage)
{
	std::string buffer = BoostServer::Serialize(apMessage);

	delete apMessage;

	boost::recursive_mutex::scoped_lock _(m_mapGuard);
	BoostConnection* pConnection = m_idToConnection[aConnectionId];
	if (pConnection && pConnection->IsConnected() && (pConnection->IsEncrypted()))
	{
		pConnection->Write(buffer);
	}
}

void BoostServer::SendForce(uint16_t aConnectionId, Packet* apMessage)
{
	std::string buffer = BoostServer::Serialize(apMessage);

	delete apMessage;

	boost::recursive_mutex::scoped_lock _(m_mapGuard);
	BoostConnection* pConnection = m_idToConnection[aConnectionId];
	if (pConnection && pConnection->IsConnected())
	{
		pConnection->Write(buffer);
	}
}

void BoostServer::SendAll(Packet* apMessage)
{
	std::string buffer = BoostServer::Serialize(apMessage);

	delete apMessage;

	boost::recursive_mutex::scoped_lock _(m_mapGuard);

	for (auto itor = m_idToConnection.begin(), end = m_idToConnection.end(); itor != end; ++itor)
	{
		BoostConnection* pConnection = itor->second;
		if (pConnection && pConnection->IsConnected() && (pConnection->IsEncrypted()))
		{
			pConnection->Write(buffer);
		}
	}
}

void BoostServer::SendAllBut(uint16_t aExcludedConnectionId, Packet* apMessage)
{
	std::string buffer = BoostServer::Serialize(apMessage);

	delete apMessage;

	boost::recursive_mutex::scoped_lock _(m_mapGuard);

	for (auto itor = m_idToConnection.begin(), end = m_idToConnection.end(); itor != end; ++itor)
	{
		BoostConnection* pConnection = itor->second;
		if (itor->first != aExcludedConnectionId && pConnection && pConnection->IsConnected() && (pConnection->IsEncrypted()))
		{
			pConnection->Write(buffer);
		}
	}
}