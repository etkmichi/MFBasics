/*
 * MFTaskThread.cpp
 *
 *  Created on: 08.07.2019
 *      Author: michl
 */
#include "MFTaskThread.h"
#include "../MFTime/MFTickCounter.h"

int MFTaskThread::s_taskThreadCount=0;
std::mutex* MFTaskThread::sp_initResourcesLock=new std::mutex();

MFTaskThread::MFTaskThread(std::string threadName,bool startThread):
		lockResources(),
		lockIdle(),
		m_isLocked(false){
	m_stop=false;
	m_stopped=false;
	m_wasStarted=false;
	sp_initResourcesLock->lock();
	m_taskThreadID=s_taskThreadCount;
	s_taskThreadCount++;
	sp_initResourcesLock->unlock();
	m_vecTasks={};
	lockIdle.lock();/*used to sleep if no task is available. if new task is added, the run method will continue because in the add function lockIdle.unlock() is called.*/
	m_threadName=threadName;
	m_sleepUntil=U_Clock::now();
	m_pauseTime=U_ClockDuration(m_sleepUntil-m_sleepUntil);
	mp_executingThread=nullptr;
	m_lockUntil.try_lock();
	m_lockFor.try_lock();
	pTicker=new MFTickCounter();
	pTicker->start();
	if(startThread){
		startDetached();
	}
	pTaskCallback=new MFCallbackTask();
	pTaskCallback->setRedoOnFailure(false);
	pTaskCallback->deleteAfterExecution(false);
}

MFTaskThread::~MFTaskThread(){
	sp_initResourcesLock->lock();
	m_stop=true;
	s_taskThreadCount--;
	m_taskThreadID=-1;
	sp_initResourcesLock->unlock();
	lockVecTasks.lock();
	//TODO clear or delete all tasks???
	std::cout<<"MFTaskThread will be destroyed - Remaining tasks: "<<m_vecTasks.size()<<std::endl;
	m_vecTasks.clear();
	try{
		delete(mp_executingThread);
		m_stopped=true;
	}catch(std::exception &e){
		std::cout<<"MFTaskThread delete(executingThread) failed!"<<m_vecTasks.size()<<std::endl;
	}
	lockVecTasks.unlock();
}

int MFTaskThread::addCallback(MFICallback *pCallback){
  lockCallbackTask.lock();
  int callbackIndex=pTaskCallback->addCallback(pCallback);
  if(!m_isCallbackEnqueued){
    lockVecTasks.lock();
    addTask(pTaskCallback);
    m_isCallbackEnqueued=true;
    lockVecTasks.unlock();
  }
  lockCallbackTask.unlock();
  return callbackIndex;
}

int MFTaskThread::addTask(MFAbstractTask* pTask){
	int ret=-1;
	lockVecTasks.lock();
	m_vecTasks.push_back(pTask);
	ret = m_vecTasks.size();
	lockResources.lock();
	if(m_isLocked){
		/*thread will continue run if no task was available.*/
		m_isLocked=false;
		lockIdle.unlock();
	}
	lockResources.unlock();
	lockVecTasks.unlock();
	return ret;
}

void MFTaskThread::startDetached(){
	lockResources.lock();
	if(!m_wasStarted || m_stopped){
		if(mp_executingThread==nullptr){
			std::cout<<"MFTaskThread::startDetached - mp_executingThread==nullptr, "
					"creating new thread!"<<std::endl;
			mp_executingThread=new std::thread(&MFTaskThread::run,this);
		}
		m_wasStarted=true;
		m_stop=false;
		m_stopped=false;
		mp_executingThread->detach();
	}
	lockResources.unlock();
}

void MFTaskThread::startJoin(){
	if(mp_executingThread==nullptr)
		mp_executingThread=new std::thread(&MFTaskThread::run,this);
	if(mp_executingThread->joinable()){
		mp_executingThread->join();
	}else{
		std::cout<<"MFTaskThread::startJoin - Thread is not joinable!\n";
	}
}

void MFTaskThread::wakeUp(){
	m_lockUntil.unlock();
}

void MFTaskThread::run(){
	lockResources.lock();
	m_posixThread=pthread_self();
	bool run=!m_stop;
	int size=0;
	bool done=false;
	m_stopped=false;
	m_started=true;
	pthread_setname_np(m_posixThread, m_threadName.data());
	lockResources.unlock();
//	try{
		while(run){
			m_lockUntil.try_lock_until(m_sleepUntil);//blocks till time is reached or lock..
			if(m_doPause){
	      pauseSustain=pauseTime-pTicker->stop();
			  if(pauseSustain>0){
//	        MFObject::printInfo(
//	            "MFTaskThread::run - try lock thread millis count: "+std::to_string(pauseSustain),
//	            m_printIndex);
	        m_lockFor.try_lock_for(U_MillisDuration(pauseSustain));
			  }else{
	        pTicker->start();
			  }
			}

			lockVecTasks.lock();
			size=m_vecTasks.size();
			if(size==0){
				lockResources.lock();
				m_isLocked=true;
				lockResources.unlock();
				lockVecTasks.unlock();
				/*lockIdle should already be in use -> this call will lead to sleep until
				 * lockIdle is unlocked.*/
				lockIdle.lock();
				continue;
			}
			currentTask=m_vecTasks.at(0);
			m_vecTasks.erase(m_vecTasks.begin());
			lockVecTasks.unlock();
			if(currentTask!=nullptr){
				preExecution();
				done=currentTask->execute();
				postExecution();
				if(!done){
					if(!currentTask->redoOnFailure()){
						MFObject::printErr("MFTaskThread::run() - sth went wrong, "
						   "task returned false!\n"
							"Thread name-ID: "+m_threadName+"-"+std::to_string(m_taskThreadID)+"\n"
              "Task name: "+currentTask->getTaskName(),
							m_printIndex);
					}else{
						addTask(currentTask);
						run=!m_stop;
						continue;
					}
				}
			}else{
				MFObject::printErr("task pointer is nullptr!\n"+
						std::to_string(m_taskThreadID),m_printIndex);
				std::cout<<"MFTaskThread::run() current task == nullptr!!: "
						<<std::endl;
			}
      run=!m_stop;

      if(currentTask==pTaskCallback)
        m_isCallbackEnqueued=false;

      if(currentTask->isDeletable()){
        delete currentTask;
        currentTask=nullptr;
      }
      if(m_repeateTasks && currentTask!=nullptr){
        addTask(currentTask);
      }
		}
//	}catch (std::exception& e) {
//		MFObject::printErr("MFTaskThread::run() - "
//				"Exception caught in run function of MFTaskThread: "+
//				std::string(e.what())+" "+std::to_string(m_taskThreadID),m_printIndex);
//		std::cout<<"MFTaskThread::run() exception: "<<e.what()<<std::endl;
//	};
	m_stopped=true;
}

void MFTaskThread::clearTasks(){
  lockVecTasks.lock();
  m_vecTasks.clear();
  lockVecTasks.unlock();
}
void MFTaskThread::stop(){
	lockResources.lock();
	m_stop=true;
	wakeUp();
	if(!lockIdle.try_lock()){
		lockIdle.unlock();
	}
	lockResources.unlock();
}

void MFTaskThread::setThreadName(std::string threadName){
	lockResources.lock();
	m_threadName=threadName;
	if(m_started)
		pthread_setname_np(m_posixThread, m_threadName.data());
	else
		m_rename=true;
	lockResources.unlock();
}



