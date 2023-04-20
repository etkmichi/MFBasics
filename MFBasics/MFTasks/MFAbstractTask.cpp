/*
 * MFAbstractTask.cpp
 *
 *  Created on: 09.07.2019
 *      Author: michl
 */
#include "MFAbstractTask.h"
#include "../MFBasicDefines.h"
#include "../MFTime/MFTickCounter.h"

MFAbstractTask::MFAbstractTask():
	lockResources(),
	lockTimeResources(){
	lockResources.lock();
//	mp_executingThread=nullptr;
	m_isDone=false;
	lockResources.unlock();
	lockTimeResources.lock();
	m_timestampCreation=MFTickCounter::current();
	m_timestampExecuteStart=MFTickCounter::current();
	m_timestampExecuteStop=MFTickCounter::current();
	m_timestampExecuteSum=0.0f;
	lockTimeResources.unlock();
}

MFAbstractTask::~MFAbstractTask(){

}
/**
 * Sets the thread which executes this task.
 * @param thread
 */
//void MFAbstractTask::setThread(MFTaskThread* thread){
//	lockResources.lock();
//	mp_executingThread=thread;
//	lockResources.unlock();
//}

//MFTaskThread* MFAbstractTask::getThread(){
//	MFTaskThread* ret;
//	lockResources.lock();
//	ret=mp_executingThread;
//	lockResources.unlock();
//	return ret;
//}

bool MFAbstractTask::isDone(){
	bool ret;
	lockResources.lock();
	ret=m_isDone;
	lockResources.unlock();
	return ret;
}

int64_t MFAbstractTask::getLastExecutionTime(){
  lockTimeResources.lock();
  int64_t ret=m_timeLatestExecution;
  lockTimeResources.unlock();
  return ret;
}

bool MFAbstractTask::execute(){
	if(m_minCallInterval>0){
		m_timeDuration=getTimeSinceLastExecutionStart();
		lockTimeResources.lock();
		if(m_timeDuration<m_minCallInterval){
			lockTimeResources.unlock();
			return true;
		}
	}
  if(m_pauseTime>0){
    m_timeDuration=getTimeSinceLastExecutionEnd();
    lockTimeResources.lock();
    if(m_timeDuration<m_pauseTime){
      lockTimeResources.unlock();
      return true;
    }
  }
	m_timestampExecuteStart=MFTickCounter::current();
	lockTimeResources.unlock();
	bool done=doWork();
	lockResources.lock();
	m_isDone=done;
	lockResources.unlock();
	lockTimeResources.lock();
	m_timestampExecuteStop=MFTickCounter::current();
	m_timeLatestExecution=MFTickCounter::ticksSince(m_timestampExecuteStart);
	m_timestampExecuteSum += m_timeLatestExecution;
	m_timestampSumCounter++;
//  if(getTaskName()==std::string("MFPhysicsModule - Task"))
//    P_INF("\n"+getTaskName()+" start/stop/duration: "+
//      T_S(m_timestampExecuteStart)+"/"+
//      T_S(m_timestampExecuteStop)+"/"+
//      T_S(m_timestampExecuteStop-m_timestampExecuteStart)+"/");
	lockTimeResources.unlock();
	if(m_deleteAfterExecution){
		m_isDeletable=true;
	}
	return done;
}

void MFAbstractTask::setRedoOnFailure(bool enable){
	m_reDoOnFailure=enable;
}

bool MFAbstractTask::redoOnFailure(){
	return m_reDoOnFailure;//used by task thread
}

int64_t MFAbstractTask::getTimeSinceLastExecutionStart(){
  lockTimeResources.lock();
	int64_t timeDuration=MFTickCounter::millisSince(m_timestampExecuteStart);
	lockTimeResources.unlock();
	return timeDuration;
}
int64_t MFAbstractTask::getTimeSinceLastExecutionEnd(){
  lockTimeResources.lock();
  int64_t timeDuration=MFTickCounter::millisSince(m_timestampExecuteStop);
  lockTimeResources.unlock();
  return timeDuration;
}
double MFAbstractTask::getAverageExecutionTime(){
	lockTimeResources.lock();
	double average=1.0*m_timestampExecuteSum/m_timestampSumCounter;
	m_timestampExecuteSum=average;
	m_timestampSumCounter=1;
	lockTimeResources.unlock();
	return average;
}
void MFAbstractTask::setPauseTime(int64_t millis){
	lockTimeResources.lock();
	m_pauseTime=millis;
	lockTimeResources.unlock();
}
bool MFAbstractTask::doWork(){
	printErr("MFAbstractTask::doWork() - Abstract function with no funtional body called!");
	return false;
}
bool MFAbstractTask::undoWork(){
	printWarning("MFAbstractTask::undoWork() - Abstract function with no funtional body called!");
	return false;
}
