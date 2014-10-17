#include "BoostServer.h"
#include "BoostManager.h"
#include "BoostConnection.h"
#include "BoostAcceptor.h"
#include "easylogging++.h"

#include "dh.h"
#include "osrng.h"

_INITIALIZE_EASYLOGGINGPP

class KeyExchangePacket : public Packet
{
public:
	void Deserialize(ReadBuffer* pBuffer)
	{
	}

	void Serialize(WriteBuffer* pBuffer)
	{
		pBuffer->WriteRaw(buffer.GetBuffer(), buffer.Size());
	}

	WriteBuffer buffer;
};

class KeyAgreement
{
public:

	KeyAgreement()
	{
		CryptoPP::Integer p("0xB10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C6"
			"9A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C0"
			"13ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD70"
			"98488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0"
			"A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708"
			"DF1FB2BC2E4A4371");

		CryptoPP::Integer g("0xA4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507F"
			"D6406CFF14266D31266FEA1E5C41564B777E690F5504F213"
			"160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1"
			"909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28A"
			"D662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24"
			"855E6EEB22B3B2E5");

		CryptoPP::Integer q("0xF518AA8781A8DF278ABA4E7D64B7CB9D49462353");
	
		CryptoPP::AutoSeededRandomPool rnd;

		m_diffieContext.AccessGroupParameters().Initialize(p, q, g);
		m_privateKey.resize(m_diffieContext.PrivateKeyLength());
		m_publicKey.resize(m_diffieContext.PublicKeyLength());

		m_diffieContext.GenerateKeyPair(rnd, m_privateKey, m_publicKey);
	}

	void Serialize(WriteBuffer* apBuffer)
	{
		apBuffer->Write_uint16((uint16_t)m_publicKey.SizeInBytes());
		apBuffer->WriteRaw(m_publicKey.BytePtr(), m_publicKey.SizeInBytes());
	}

	std::string Agree(ReadBuffer* apBuffer)
	{
		std::string sharedSecret(m_diffieContext.AgreedValueLength(), '\0');

		uint16_t length = 0;
		apBuffer->Read_uint16(length);

		if (length == m_diffieContext.PublicKeyLength())
		{
			CryptoPP::SecByteBlock remotePublicKey(length);

			apBuffer->ReadRaw(remotePublicKey.BytePtr(), length);

			if (m_diffieContext.Agree((uint8_t*)&sharedSecret[0], m_privateKey, remotePublicKey))
			{
				return sharedSecret;
			}
		}

		return std::string();
	}
private:

	CryptoPP::DH m_diffieContext;
	CryptoPP::SecByteBlock m_privateKey;
	CryptoPP::SecByteBlock m_publicKey;
};

BoostServer::BoostServer()
	: m_lightTaskManager(4)
	, m_mediumTaskManager(4)
	, m_heavyTaskManager(4)
	, m_ipv4Acceptor(0)
	, m_ipv6Acceptor(0)
	, m_idPool(65535)
	, m_keyAgreement(new KeyAgreement)
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

	delete m_keyAgreement;
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
				while ((pBuffer = pConnection->Consume()) != nullptr)
				{
					// If the connection is encrypted data go to the user
					if (pConnection->IsEncrypted())
					{
						OnConsume(pConnection->GetId(), pBuffer);
					}
					// If not we are still in the handshake process
					else
					{
						HandleKeyExchange(pConnection, pBuffer);
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

void BoostServer::HandleKeyExchange(BoostConnection* apConnection, ReadBuffer* apBuffer)
{
	uint8_t type = 0;
	apBuffer->Read_uint8(type);
	switch (type)
	{
	case 0:
	{
		std::string sharedSecret = m_keyAgreement->Agree(apBuffer);
		if (sharedSecret.size() == 0)
		{
			apConnection->Close();
			return;
		}
		apConnection->SetSharedSecret(sharedSecret);

		KeyExchangePacket* packet = new KeyExchangePacket();
		m_keyAgreement->Serialize(&packet->buffer);

		SendForce(apConnection->GetId(), packet);
	}
		break;
	case 1:
	{
		uint32_t magic;
		apBuffer->Read_uint32(magic);
		if (magic == 0x12345678)
		{
			apConnection->EnableEncryption();
			OnConnection(apConnection->GetId());
			return;
		}
	}
	default:

		apConnection->Close();
		break;
	}

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