/*
 * MFTaskThread.h
 *
 *  Created on: 08.07.2019
 *      Author: michl
 */

#ifndef MFTHREADSYSTEM_MFTASKTHREAD_H_
#define MFTHREADSYSTEM_MFTASKTHREAD_H_

#include "../MFTasks/MFAbstractTask.h"
#include "MFIWakableThread.h"
#include "../MFTime/MFTimeStructs.h"
#include "../MFPrinters/MFPrintSetup.h"
#include "../MFTime/MFTickCounter.h"
#include "../MFTasks/MFCallbackTask.h"
#include <pthread.h>
#include <mutex>
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <atomic>
#include <ctime>
#include <x86intrin.h>
/**TODO pthread is not compatible with windows...
 * This class is a thread class which executes and manages MFTasks
 */
class MFTaskThread :
    public MFIWakableThread,
    public MFPrintSetup{
private:
  MFTickCounter
  *pTicker;

	std::string
  m_threadName;

	pthread_t
  m_posixThread;

	static int
  s_taskThreadCount;

	static std::mutex
  *sp_initResourcesLock;

	std::thread
  *mp_executingThread;

	std::mutex
  lockCallbackTask,
  lockVecTasks,
  lockResources,
  lockIdle;

	std::vector<MFAbstractTask*>
  m_vecTasks;

	bool
  m_wasStarted=false,
  m_isLocked,
  m_stop,
  m_stopped,
  m_started=false,
  m_doPause=false,
  m_rename=false,
  m_repeateTasks=false,
  m_isCallbackEnqueued=false;

	MFCallbackTask
	*pTaskCallback;

	int
  m_taskThreadID;

	U_TimePoint
  m_sleepUntil;

	U_ClockDuration
  m_pauseTime,
  m_remainingPauseTime;

	int64_t
  pauseTime,
  pauseSustain;

	std::timed_mutex
  m_lockUntil,
  m_lockFor;

	MFAbstractTask*
  currentTask=nullptr;

protected:/*virtual functions MFTaskThread*/
  virtual void run();
  virtual void preExecution(){};
  virtual void postExecution(){};
public:
	MFTaskThread(std::string threadName,bool startThread=true);
	virtual ~MFTaskThread();
	int addTask(MFAbstractTask *pTask);/*TODO disable task with returned index*/
	int addCallback(MFICallback *pCallback);/*TODO disable callback with ret index*/
	void stop();
	void wakeUp();
	void clearTasks();

	/**
	 * Starts the thread independent of the calling thread.
	 */
	void startDetached();

	/**
	 * Starts the thread on the calling thread.
	 */
	void startJoin();

	bool isStopped(){return m_stopped;};
	bool isStarted(){return m_started;};
	std::thread::id getThreadID(){return mp_executingThread->get_id();};

	/**
	 * Before next iteration this thread's run funtion will sleep until the specified time point.
	 * @param sleepUntil
	 */
	void setSleepUntil(U_TimePoint sleepUntil){
		m_sleepUntil=sleepUntil;
	}
	void setSleepUntil(int64_t timepoint){
		U_ClockDuration dur(timepoint);
		m_sleepUntil=U_TimePoint(dur);
//		std::time_t t=Clock::to_time_t(m_sleepUntil);
//		MFObject::printInfo("Debug MFTaskThread::setSleepUntil - \ntime point: "+
//				std::to_string(m_sleepUntil.time_since_epoch().count()));
//		MFObject::printInfo("Debug MFTaskThread::setSleepUntil - \nparameter: "+
//				std::to_string(timepoint));
//		MFObject::printInfo("Debug MFTaskThread::setSleepUntil\nreadable time:"+
//				std::string(std::ctime(&t)));
	};

	uint64_t getCPUTicker(){
		uint32_t lo,hi;
		__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
		return ((uint64_t)hi<<32)|lo;
	}

	void enablePauseTime(
			bool enable,
			int64_t pauseMillis){
		m_doPause=enable;
		m_pauseTime=U_ClockDuration(pauseMillis);
	}

	void setPauseTime(
			int64_t pauseMillis=0,
			bool enable=true){
		m_doPause=enable;
		m_pauseTime=U_ClockDuration(pauseMillis);
		this->pauseTime=pauseMillis;
		pTicker->start();
	}
	void setThreadName(std::string threadName);

	/**
	 * If task repeat is enabled, the task will be enqueued again after it's execution.
	 * @param enable
	 */
	void enableTaskRepeat(bool enable){m_repeateTasks=enable;};
};


#endif /* MFTHREADSYSTEM_MFTASKTHREAD_H_ */
