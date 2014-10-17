#ifndef CORE_TASK_MANAGER_H
#define CORE_TASK_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#define WIN32_LEAN_AND_MEAN 

#include <boost/thread.hpp>
#include "Semaphore.h"

/*!
* \class Task
*
* \brief Pure virtual interface to use when creating tasks.
*
*/
class Task
{
public:

	/**
	 * @brief Executes in the background.
	 *
	 * Executes in the background.
	 *
	 * @return true to schedule mainthread work or false to run in the background again.
	 */
	virtual bool DoBackgroundTask() = 0;
	/**
	* @brief Executes in the main thread.
	*
	* Executes in the main thread.
	*
	* @return true to delete self, false to run in mainthread again.
	*/
	virtual bool DoMainthreadTask() = 0;
};

/*!
* \class TaskManager
*
* \brief Used to manage tasks and make better use of threads. Thread safe.
*
*/
class TaskManager
{
public:

	/**
	 * @brief Constructs a TaskManager.
	 *
	 * Constructs a TaskManager.
	 *
	 * @param aThreadCount The number of threads to start for background processing. Will clamp in [1; +oo[
	 */
	TaskManager(uint16_t aThreadCount);
	~TaskManager();

	/**
	 * @brief Schedule a task for background work.
	 *
	 * Schedule a task for background work. This call is thread safe.
	 *
	 * @param pTask The task to schedule.
	 */
	void AddTask(Task* pTask);

	/**
	* @brief Schedule a task for mainthread work.
	*
	* Schedule a task for mainthread work. This call is thread safe.
	*
	* @param pTask The task to schedule.
	*/
	void AddMainTask(Task* pTask);

	/**
	 * @brief Executes all main thread tasks.
	 *
	 * Executes all main thread tasks. This function must be ran from the main thread.
	 *
	 */
	void Gather();

private:

	void Work();

	std::list <Task*>			m_backgroundTasks;
	std::list <Task*>			m_mainTasks;
	std::list <boost::thread*>	m_threads;
	Semaphore					m_taskSemaphore;
	boost::recursive_mutex		m_mainTaskLock;
	boost::recursive_mutex		m_backgroundLock;

	bool m_running;
};


#endif // CORE_TASK_MANAGER_H