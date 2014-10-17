#ifndef CORE_SEMAPHORE_H
#define CORE_SEMAPHORE_H

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>    
#include <boost/thread/lock_types.hpp>

/*!
* \class Semaphore
*
* \brief A countable semaphore implementation. Thread safe.
*
*/
class Semaphore
{
public:
	/**
	 * @brief Construct a Semaphore.
	 *
	 * Constructs a Semaphore.
	 *
	 * @param aInitialCount Initial value of the semaphore. 0 to make it empty.
	 * @return 
	 */
	explicit Semaphore(uint32_t aInitialCount);

	/**
	 * @brief Get the value of the semaphore.
	 *
	 * Get the value of the semaphore.
	 *
	 * @return The value of the semaphore.
	 */
	uint32_t GetCount();

	/**
	 * @brief Increments the value of the semaphore and unlocks a thread if one is waiting.
	 *
	 * Increments the value of the semaphore and unlocks a thread if one is waiting.
	 */
	void Signal();

	/**
	 * @brief Decrements the value of the semaphore if value > 0 or block until Signal is called.
	 *
	 * Decrements the value of the semaphore if value > 0 or block until Signal is called.
	 *
	 */
	void Wait();

private:

	uint32_t m_count;
	boost::mutex m_mutex;
	boost::condition_variable m_condition;
};



#endif