#ifndef NETWORK_BOOST_CONNECTION_H
#define NETWORK_BOOST_CONNECTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define WIN32_LEAN_AND_MEAN 

#include "Buffer.h"
#include <boost/atomic.hpp>
#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>

class BoostConnection : boost::noncopyable
{
public:
    BoostConnection(boost::asio::io_service& pIoStream, uint16_t aId = 0);
    ~BoostConnection();

    /**
     * @brief Connect to a remote host. UNTESTED.
     *
     * Connect to a remote host. Do not use as this function is untested.
     *
     * @param aIp The remote IP to connect to.
     * @param aPort The remote port to connect to. 
     */
    void Connect(const std::string& aIp, uint16_t aPort);

    /**
     * @brief Writes data to the socket.
     *
     * Writes data to the socket. This function is async, it will post a job to write and will add the size header.
	 * If the connection has encryption enabled it will also encrypt the data.
     *
     * @param apBuffer The data to send.
     */
	void Write(const std::string& apBuffer);

    /**
     * @brief Consume a packet in queue.
     *
     * Consume a packet in queue.
     *
     * @return nullptr if no packet is available or the packet.
     */
    bool Consume(ReadBuffer*& apBuffer);

    /**
     * @brief Close the connection.
     *
     * Close the connection if connected, else does nothing.
     *
     */
    void Close();

    /**
     * @brief Get the internal socket used.
     *
     * Get the internal socket used.
     *
     * @return The socket used.
     */
    boost::asio::ip::tcp::socket& GetSocket() { return m_socket; }

    /**
     * @brief Get if the connection is connected or not.
     *
     * Get if the connection is connected or not.
     *
     * @return true if connected, false if not.
     */
    bool IsConnected();

	/**
	 * @brief Get if the connection is using a stream cipher.
	 *
	 * Get if the connection is using a stream cipher. The server should not send or handle application logic packets if this not true.
	 *
	 * @return true if encrypted, false if not.
	 */
	bool IsEncrypted() const;

    /**
     * @brief Used internally to mark a connection as orphaned/closed and must be deleted.
     *
     * Used internally to mark a connection as orphaned/closed and must be deleted.
     *
     */
    void MarkForDelete() { m_markedForDelete = true; }
    /**
     * @brief Used internally to check if a connection needs to be deleted.
     *
     * Used internally to check if a connection needs to be deleted.
     *
     * @return true if the object needs to be deleted.
     */
    bool IsMarkedForDelete() const { return m_markedForDelete; }

    /**
     * @brief Used internaly to check if it's safe to delete the object.
     *
     * Used internaly to check if it's safe to delete the object.
     *
     * @return true if the object is marked for delete and is not used in background tasks.
     */
    bool CanDelete() const { return m_markedForDelete && (m_outstandingTasks == 0); }
    /**
     * @brief Get the connection Id.
     *
     * Get the connection Id.
     *
     * @return The connection id.
     */
    uint16_t GetId() const { return m_id; }

    /**
     * @brief Marks the connection as accepted and starts reading from the socket.
     *
     * Marks the connection as accepted and starts reading from the socket.
     *
     */
    void Accept();

	/**
	 * @brief Set the shared secret.
	 *
	 * Set the shared secret and initialize stream ciphers.
	 *
	 * @param acSharedSecret The shared secret.
	 */
	void SetSharedSecret(const std::string& acSharedSecret, bool aClient);
	/**
	 * @brief Enables encryption.
	 *
	 * Enabled encryption. Should only be called internaly after handshake.
	 *
	 */
	void EnableEncryption();

private:

    void Read();
	void StartEncryptionHandshake();

	void DoWrite();

    void HandleWrite(const boost::system::error_code& aError);
    void HandleReadHeader(const boost::system::error_code& aError, size_t aBytesRead);
	void HandleReadBody(const boost::system::error_code& aError, size_t aBytesRead);
	void HandleReadEncryptionHeader(const boost::system::error_code& aError, size_t aBytesRead);
	void HandleReadEncryptionBody(const boost::system::error_code& aError, size_t aBytesRead);
    void HandleConnect(const boost::system::error_code& aError);
	void HandleResolve(const boost::system::error_code& aError, boost::asio::ip::tcp::resolver::iterator aEndpointItor);
	void HandleHandshake(ReadBuffer* apBuffer);

    boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::resolver m_resolver;

    uint16_t    m_id;
    bool        m_connected;
    bool        m_markedForDelete;
	bool		m_writeInProgress;
	bool		m_encrypted;

	boost::chrono::steady_clock::time_point m_lastEvent;
    boost::atomic<uint32_t>					m_outstandingTasks;
    uint32_t								m_incomingLength;
    std::string								m_buffer;
    boost::mutex							m_incomingQueueLock;
    boost::recursive_mutex					m_outgoingQueueLock;
    std::queue<ReadBuffer*>					m_incomingQueue;
    std::queue<std::string>					m_outgoingQueue;
	void*									m_pEncryption;
	void*									m_pDecryption;
};

#endif // NETWORK_BOOST_CONNECTION_H