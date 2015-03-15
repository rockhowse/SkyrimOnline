#include "EnetServer.h"
#include "easylogging++.h"


_INITIALIZE_EASYLOGGINGPP

void EnetServer::Initialize()
{
	enet_initialize();
	atexit(enet_deinitialize);
}

EnetServer::EnetServer()
	: m_lightTaskManager(4)
	, m_mediumTaskManager(4)
	, m_heavyTaskManager(4)
	, m_idPool(65535)
	, m_pHost(nullptr)
	, m_pServer(nullptr)
{
	std::memset(m_pPeers, 0, sizeof(ENetPeer*) * UINT16_MAX);
}

EnetServer::~EnetServer()
{
	enet_host_destroy(m_pHost);
}

bool EnetServer::Update()
{
	ENetEvent event;

	while (enet_host_service(m_pHost, &event, 0) != 0)
	{
		ReadBuffer* pBuffer = nullptr;
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			event.peer->data = (void*)m_idPool.GetId();
			m_pPeers[(uint16_t)event.peer->data] = event.peer;
			OnConnection((uint16_t)event.peer->data);
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			pBuffer = new ReadBuffer(event.packet->data, (uint32_t)event.packet->dataLength);
			OnConsume((uint16_t)event.peer->data, pBuffer);
			enet_packet_destroy(event.packet);
			delete pBuffer;
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			OnDisconnection((uint16_t)event.peer->data);
			m_pPeers[(uint16_t)event.peer->data] = nullptr;
			event.peer->data = nullptr;
			break;
		}
	}

	OnUpdate();

	boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
	
    return true;
} 

void EnetServer::Host(uint16_t aPort)
{
	m_address.host = ENET_HOST_ANY;
	m_address.port = aPort;

	m_pHost = enet_host_create(&m_address, 1024, 4, 0, 0);

	m_pServer = nullptr;
}

void EnetServer::Connect(const std::string& acHost, uint16_t aPort)
{
	m_pHost = enet_host_create(NULL, 1, 6, 0, 0);

	enet_address_set_host(&m_address, acHost.c_str());
	m_address.port = aPort;

	m_pServer = enet_host_connect(m_pHost, &m_address, 6, 0);
}

std::string EnetServer::Serialize(Packet* apMessage)
{
	WriteBuffer buffer;
	apMessage->Serialize(&buffer);

	std::string outBuffer;

	outBuffer.append((char*)buffer.GetBuffer(), buffer.Size());


	return outBuffer;
}

std::string EnetServer::Serialize(WriteBuffer* apMessage)
{
	std::string outBuffer;

	outBuffer.append((char*)apMessage->GetBuffer(), apMessage->Size());

	return outBuffer;
}

std::string EnetServer::Serialize(const std::string& aMessage)
{
	std::string outBuffer;
	outBuffer.append((char*)aMessage.data(), aMessage.size());


	return outBuffer;
}

void EnetServer::Send(uint16_t aConnectionId, Packet* apMessage)
{
	std::string buffer = EnetServer::Serialize(apMessage);

	delete apMessage;

	if (m_pServer != nullptr)
	{
		ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
		enet_peer_send(m_pServer, 0, pPacket);
	}
	else
	{
		auto pPeer = m_pPeers[aConnectionId];
		if (pPeer != nullptr)
		{
			ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
			enet_peer_send(pPeer, 0, pPacket);
		}
	}
}

void EnetServer::SendReliable(uint16_t aConnectionId, Packet* apMessage)
{
	std::string buffer = EnetServer::Serialize(apMessage);

	delete apMessage;

	if (m_pServer != nullptr)
	{
		ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(m_pServer, 0, pPacket);
	}
	else
	{
		auto pPeer = m_pPeers[aConnectionId];
		if (pPeer != nullptr)
		{
			ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(pPeer, 0, pPacket);
		}
	}
}

void EnetServer::SendAll(Packet* apMessage)
{
	std::string buffer = EnetServer::Serialize(apMessage);

	delete apMessage;

	if (m_pServer != nullptr)
	{
		return;
	}
	else
	{
		ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
		enet_host_broadcast(m_pHost, 0, pPacket);
	}
}

void EnetServer::SendReliableAll(Packet* apMessage)
{
	std::string buffer = EnetServer::Serialize(apMessage);

	delete apMessage;

	if (m_pServer != nullptr)
	{
		return;
	}
	else
	{
		ENetPacket* pPacket = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(m_pHost, 0, pPacket);
	}
}
