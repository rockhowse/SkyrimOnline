#include "BoostAcceptor.h"
#include "BoostConnection.h"

BoostAcceptor::BoostAcceptor(uint16_t aPort, Listener* apListener, NetIPv6 aIp, boost::asio::io_service& aIoService)
    : m_pListener(apListener)
    , m_acceptor(aIoService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), aPort))
{
    boost::system::error_code ec;
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
}

BoostAcceptor::BoostAcceptor(uint16_t aPort, Listener* apListener, NetIPv4 aIp, boost::asio::io_service& aIoService)
    : m_pListener(apListener)
    , m_acceptor(aIoService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), aPort))
	, m_pConnection(nullptr)
{
    boost::system::error_code ec;
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
}

BoostAcceptor::~BoostAcceptor()
{
    m_acceptor.close();
	delete m_pConnection;
}

void BoostAcceptor::Accept(BoostConnection* apConnection)
{
	m_pConnection = apConnection;
    m_acceptor.async_accept(apConnection->GetSocket(),
			boost::bind(&BoostAcceptor::HandleAccept, this,
			boost::asio::placeholders::error));
}

void BoostAcceptor::HandleAccept(const boost::system::error_code& aError)
{
    if(aError)
    {
        return;
    }

    // We give the connection accepted to the factory and in exchange it gives us a new one !
	Accept(m_pListener->OnConnection(m_pConnection));
}