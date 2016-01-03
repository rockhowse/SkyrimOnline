#ifndef NETWORK_ENET_SERVER_H
#define NETWORK_ENET_SERVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "IdGenerator.h"
#include "Packet.h"
#include "TaskManager.h"
#include "Buffer.h"

#include <unordered_map>

#include <enet/enet.h>

#define DEFAULT_SERVER_PORT 10578

class EnetServer
{
public:

	static void Initialize();

    /**
     * @brief Constructs a EnetServer.
     *
     * Constructs a EnetServer.
     *
     */
	EnetServer();
	virtual ~EnetServer();

    /**
     * @brief Updates everything.
     *
     * Updates everything, must be called from mainthread.
     *
     * @return true if the server still wants to run.
     */
    bool Update();

    /**
     * @brief User Update handler.
     *
     * User Update handler, called everyframe by Update()
     *
     */
    virtual void OnUpdate() = 0;
    /**
     * @brief User connection handler.
     *
     * User connection handler.
	 * This function will be called once a connection has gone through handshake and key exchange.
     *
     * @param aConnectionId The Id of the connection accepted.
     */
    virtual void OnConnection(uint16_t aConnectionId) = 0;
	/**
	* @brief User disconnection handler.
	*
	* User disconnection handler.
	* This function will be called once a connection was lost.
	*
	* @param aConnectionId The Id of the connection lost.
	*/
    virtual void OnDisconnection(uint16_t aConnectionId) = 0;
	/**
	 * @brief User consume handler.
	 *
	 * User consume handler.
	 *
	 * @param aConnectionId The connection id from which the packet came.
	 * @param pBuffer The packet buffer, do not delete it, it will be taken care of.
	 * @return 
	 */
	virtual void OnConsume(uint16_t aConnectionId, ReadBuffer* pBuffer) = 0;
    
	/**
	* @brief Hosts a server on port for IPv4 and port + 1 for IPv6.
	*
	* Attempts to read from ServerConfing.ini for a specific IP and port
	* If that fails it uses the default address of ENET_HOST_ANY
	*/
	void Host();

    /**
     * @brief Hosts a server on port for IPv4 and port + 1 for IPv6.
     *
     * Hosts a server on port for IPv4 and port + 1 for IPv6.
     *
     * @param aPort The port to host on.
     */
    void Host(uint16_t aPort);

	void Connect(const std::string& acHost, uint16_t aPort);

	/**
	* @brief Send a reliable packet to a connection.
	*
	* Force Send a reliable packet to a connection.
	*
	* @param aConnectionId The connection to send it to.
	* @param apMessage The message to send.
	*/
	void SendReliable(uint16_t aConnectionId, Packet* apMessage);

	/**
	* @brief Send a packet to a connection.
	*
	* Send a packet to a connection.
	*
	* @param aConnectionId The connection to send it to.
	* @param apMessage The message to send.
	*/
	void Send(uint16_t aConnectionId, Packet* apMessage);

	/**
	* @brief Send a reliable packet to a connection.
	*
	* Force Send a reliable packet to a connection.
	*
	* @param apMessage The message to send.
	*/
	void SendReliableAll(Packet* apMessage);

	/**
	* @brief Send a packet to a connection.
	*
	* Send a packet to a connection.
	*
	* @param apMessage The message to send.
	*/
	void SendAll(Packet* apMessage);

	TaskManager* GetLightTaskManager() { return &m_lightTaskManager; }
	TaskManager* GetMediumTaskManager() { return &m_mediumTaskManager; }
	TaskManager* GetHeavyTaskManager() { return &m_heavyTaskManager; }

	static std::string Serialize(Packet* apMessage);

	static std::string Serialize(WriteBuffer* apMessage);

	static std::string Serialize(const std::string& aMessage);

protected:

	TaskManager			m_lightTaskManager;
	TaskManager			m_mediumTaskManager;
	TaskManager			m_heavyTaskManager;

private:

    IdGenerator							m_idPool;
    
	ENetAddress							m_address;
	ENetHost*							m_pHost;
	ENetPeer*							m_pPeers[UINT16_MAX];
	ENetPeer*							m_pServer;
};

#endif // NETWORK_ENET_SERVER_H