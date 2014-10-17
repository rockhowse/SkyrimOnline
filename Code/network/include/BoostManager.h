#ifndef NETWORK_BOOST_MANAGER_H
#define NETWORK_BOOST_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define WIN32_LEAN_AND_MEAN 

#include <boost/asio.hpp>
#include <boost/thread.hpp>

class BoostConnection;
class BoostManager
{
public:

    /**
     * @brief Setup the io services.
     *
     * Setup the io services.
     *
     * @param aThreadCount The number of io services and threads to use.
     */
    static void Setup(uint32_t aThreadCount);

    /**
     * @brief Stops all threads and ends all io services.
     *
     * Stops all threads and ends all io services.
	 * Calling this function without destroying all users of the io services will cause the process to crash.
     *
     */
    static void Destroy();

	/**
	 * @brief Get an io service.
	 *
	 * Get an io service. This is using a round robin load balancing algorithm.
	 *
	 * @return One of the io services.
	 */
	boost::asio::io_service& GetIoService();

	/**
	 * @brief Get the instance of the BoostManager.
	 *
	 * Get the instance of the BoostManager.
	 *
	 * @return The instance of the BoostManager.
	 */
	static BoostManager& GetInstance();

private:

	BoostManager();
	~BoostManager();

	struct IOPool
	{
		IOPool();
		~IOPool();

		boost::asio::io_service m_ioService;
		boost::asio::io_service::work m_work;
		boost::thread* m_thread;
	};

	IOPool* m_pools;
	uint32_t m_poolCount;
	uint32_t m_poolCursor;
};

#endif // NETWORK_BOOST_MANAGER_H