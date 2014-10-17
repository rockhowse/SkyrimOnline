#include "TaskManager.h"

#include <boost/date_time/posix_time/posix_time.hpp>

TaskManager::TaskManager(uint16_t aThreadCount)
	: m_running(true)
	, m_taskSemaphore(0)
{
	aThreadCount = std::max(aThreadCount, (uint16_t)1);

	for (uint16_t i = 0; i < aThreadCount; ++i)
	{
		m_threads.push_back(new boost::thread(&TaskManager::Work, this));
	}
}

TaskManager::~TaskManager()
{
	m_running = false;

	m_taskSemaphore.Signal();

	for (auto t : m_threads)
	{
		t->join();
		delete t;
	}
}

void TaskManager::AddTask(Task* pTask)
{
	boost::recursive_mutex::scoped_lock _(m_backgroundLock);

	m_backgroundTasks.push_back(pTask);

	m_taskSemaphore.Signal();
}

void TaskManager::AddMainTask(Task* pTask)
{
	boost::recursive_mutex::scoped_lock _(m_mainTaskLock);

	m_mainTasks.push_back(pTask);
}

void TaskManager::Gather()
{
	boost::recursive_mutex::scoped_lock _(m_mainTaskLock);

	auto itor = m_mainTasks.begin();
	auto end = m_mainTasks.end();
	for (; itor != end; ++itor)
	{
		if ((*itor)->DoMainthreadTask())
		{
			delete *itor;
			itor = m_mainTasks.erase(itor);
			if (itor == end)
			{
				break;
			}
		}
	}
}

void TaskManager::Work()
{
	while (true)
	{
		Task* pTask = nullptr;
		{
			m_taskSemaphore.Wait();

			if (!m_running)
			{
				// Chain unlock everyone
				m_taskSemaphore.Signal();
				return;
			}
			
			boost::recursive_mutex::scoped_lock _(m_backgroundLock);
			
			pTask = m_backgroundTasks.front();
			m_backgroundTasks.pop_front();
		}

		if (pTask)
		{
			bool res = pTask->DoBackgroundTask();
			if (res == false)
			{
				AddTask(pTask);
			}
			else
			{
				AddMainTask(pTask);
			}
		}
	}
}