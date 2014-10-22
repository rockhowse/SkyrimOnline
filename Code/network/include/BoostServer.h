#ifndef NETWORK_BOOST_SERVER_H
#define NETWORK_BOOST_SERVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "BoostAcceptor.h"
#include "IdGenerator.h"
#include "Packet.h"
#include "TaskManager.h"
#include "Buffer.h"

#include <unordered_map>

class BoostConnection;
class BoostServer : public BoostAcceptor::Listener
{
public:

    /**
     * @brief Constructs a BoostServer.
     *
     * Constructs a BoostServer.
     *
     */
	BoostServer();
    virtual ~BoostServer();

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


    BoostConnection* OnConnection(BoostConnection* apConnection);
    
    /**
     * @brief Hosts a server on port for IPv4 and port + 1 for IPv6.
     *
     * Hosts a server on port for IPv4 and port + 1 for IPv6.
     *
     * @param aPort The port to host on.
     */
    void Host(uint16_t aPort);

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
	* @brief Send a packet to all active connections.
	*
	* Send a packet to all active connections.
	*
	* @param apMessage The message to send.
	*/
	void SendAll(Packet* apMessage);

	/**
	* @brief Send a packet to all active connections except for one.
	*
	* Send a packet to all active connections except for one.
	*
	* @param aExcludedConnectionId The connection to exclude.
	* @param apMessage The message to send.
	*/
	void SendAllBut(uint16_t aExcludedConnectionId, Packet* apMessage);

	TaskManager* GetLightTaskManager() { return &m_lightTaskManager; }
	TaskManager* GetMediumTaskManager() { return &m_mediumTaskManager; }
	TaskManager* GetHeavyTaskManager() { return &m_heavyTaskManager; }

	static std::string Serialize(Packet* apMessage);

	static std::string Serialize(WriteBuffer* apMessage);

	static std::string Serialize(const std::string& aMessage);

protected:

	/**
	* @brief Force send a packet to a connection.
	*
	* Force send a packet to a connection.
	*
	* @param aConnectionId The connection to send it to.
	* @param apMessage The message to send.
	*/
	void SendForce(uint16_t aConnectionId, Packet* apMessage);


	TaskManager			m_lightTaskManager;
	TaskManager			m_mediumTaskManager;
	TaskManager			m_heavyTaskManager;

private:

	friend class PacketSenderTask;
	friend class PacketSendAllTask;
	friend class PacketSendAllButTask;

    BoostAcceptor*						m_ipv4Acceptor;
    BoostAcceptor*						m_ipv6Acceptor;
    IdGenerator							m_idPool;
    boost::recursive_mutex				m_mapGuard;
	std::unordered_map <uint16_t, BoostConnection*> m_idToConnection;
};

#endif // NETWORK_BOOST_SERVER_H