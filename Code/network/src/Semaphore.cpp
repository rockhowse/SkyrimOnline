#include "Semaphore.h"

Semaphore::Semaphore(uint32_t aInitialCount)
	: m_count(aInitialCount)
	, m_mutex()
	, m_condition()
{
}

uint32_t Semaphore::GetCount()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);
	return m_count;
}

void Semaphore::Signal()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);

	++m_count;

	m_condition.notify_one();
}

void Semaphore::Wait()
{
	boost::unique_lock<boost::mutex> lock(m_mutex);
	while (m_count == 0)
	{
		m_condition.wait(lock);
	}
	--m_count;
}