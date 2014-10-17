#ifndef NETWORK_BOOST_ACCEPTOR_H
#define NETWORK_BOOST_ACCEPTOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define WIN32_LEAN_AND_MEAN 

#include <boost/asio.hpp>

struct NetIPv6 : public std::string
{};

struct NetIPv4 : public std::string
{};

class BoostConnection;
class BoostAcceptor
{
public:

    struct Listener
    {
        /**
         * @brief Callback when a new connection is accepted.
         *
         * Callback when a new connection is accepted.
         *
         * @param apConnection The accepted connection.
         * @return A new connection to accept.
         */
        virtual BoostConnection* OnConnection(BoostConnection* apConnection) = 0;
    };

    /**
     * @brief Constructs a IPv4 Acceptor.
     *
     * Constructs a IPv4 Acceptor.
     *
     * @param aPort The port to listen on.
     * @param apListener The BoostAcceptor::Listener to use.
     * @param aIp The IPv4 to listen on.
     * @param aIoService The IO service to use.
     */
    BoostAcceptor(uint16_t aPort, Listener* apListener, NetIPv4 aIp, boost::asio::io_service& aIoService);

	/**
	* @brief Constructs a IPv6 Acceptor.
	*
	* Constructs a IPv6 Acceptor.
	*
	* @param aPort The port to listen on.
	* @param apListener The BoostAcceptor::Listener to use.
	* @param aIp The IPv6 to listen on.
	* @param aIoService The IO service to use.
	*/
    BoostAcceptor(uint16_t aPort, Listener* apListener, NetIPv6 aIp, boost::asio::io_service& aIoService);
    ~BoostAcceptor();

    /**
     * @brief Accepts a connection.
     *
     * Accepts a connection.
     *
     * @param apConnection The connection object to accept.
     */
    void Accept(BoostConnection* apConnection);

private:

    void HandleAccept(const boost::system::error_code& aError);

    Listener* m_pListener;
    boost::asio::ip::tcp::acceptor m_acceptor;
	BoostConnection* m_pConnection;
};

#endif // NETWORK_BOOST_ACCEPTOR_H