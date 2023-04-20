/*
 * MFDataDeleterThread.cpp
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#include "MFDataDeleterThread.h"

MFDataDeleterThread::MFDataDeleterThread():
MFTaskThread("MFDataDeleterThread"){
	enablePauseTime(true, 50);
	mp_deletionTask=nullptr;
	setThreadName("MFDataDeleterThread");
}

MFDataDeleterThread::~MFDataDeleterThread() {
	// TODO Auto-generated destructor stub
}

void MFDataDeleterThread::postExecution(){
	if(mp_deletionTask==nullptr){
		return;
	}
	if(mp_deletionTask->getInputDataCount()>0){
		addTask(mp_deletionTask);
		setSleepUntil(mp_deletionTask->getNextDeletionTimepoint());
	}
}
