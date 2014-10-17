#include "BoostManager.h"
#include "BoostConnection.h"

BoostManager::IOPool::IOPool()
	: m_ioService()
	, m_work(m_ioService)
{
	m_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &m_ioService));
}

BoostManager::IOPool::~IOPool()
{
	try
	{
		m_ioService.stop();
		m_thread->join();
		delete m_thread;
	}
	catch (boost::thread_interrupted&)
	{

	}
}

BoostManager& BoostManager::GetInstance()
{
	static BoostManager instance;
	return instance;
}

BoostManager::BoostManager()
	: m_pools(nullptr)
	, m_poolCount(0)
	, m_poolCursor(0)
{

}

BoostManager::~BoostManager()
{
	BoostManager::GetInstance().m_poolCount = 0;
	BoostManager::GetInstance().m_poolCursor = 0;
	delete[] BoostManager::GetInstance().m_pools;
}

boost::asio::io_service& BoostManager::GetIoService()
{
	m_poolCursor += 1;

	if (m_poolCursor >= m_poolCount)
	{
		m_poolCursor = 0;
	}

	return m_pools[m_poolCursor].m_ioService;
}

void BoostManager::Setup(uint32_t aThreadCount)
{
	BoostManager::GetInstance().m_poolCount = std::max(aThreadCount, (uint32_t)1);
	BoostManager::GetInstance().m_poolCursor = 0;
	BoostManager::GetInstance().m_pools = new IOPool[BoostManager::GetInstance().m_poolCount];
}

void BoostManager::Destroy()
{
	BoostManager::GetInstance().m_poolCount = 0;
	BoostManager::GetInstance().m_poolCursor = 0;
	delete[] BoostManager::GetInstance().m_pools;
	BoostManager::GetInstance().m_pools = nullptr;
}