/*
 * MFTaskManager.cpp
 *
 *  Created on: 18.03.2020
 *      Author: michl
 */

#include "MFTaskManager.h"

MFTaskManager::MFTaskManager() :
		MFTaskThread("MFTaskManager", false){
	mp_vecTasks=new std::vector<DispatchCollection*>();
	mp_dummyData=new DispatchCollection();
	mp_dummyData->pTask=new MFAbstractTask();
	mp_defaultDispatchThread=nullptr;
}

MFTaskManager::~MFTaskManager() {
  for(MFAbstractDataProcessingTask* pT:m_vecDeletableTasks)
    delete pT;
}

void MFTaskManager::addDeletableTask(MFAbstractDataProcessingTask* pTask){
  m_vecDeletableTasks.push_back(pTask);
}

uint32_t MFTaskManager::addTask(
		MFAbstractTask* pTask){
	return addTask(pTask,nullptr,mp_defaultDispatchThread,nullptr);
}

uint32_t MFTaskManager::addTask(
		MFAbstractTask* pTask,
		MFStructurableDataBuffer* pDataBuffer){
	return addTask(pTask,pDataBuffer,mp_defaultDispatchThread,nullptr);
}

uint32_t MFTaskManager::addTask(
		MFAbstractTask* pTask,
		MFStructurableDataBuffer* pDataBuffer,
		MFTaskThread* pTaskThread,
		MFIStructurableDataCreator* pDataCreator){
	DispatchCollection* pDC=new DispatchCollection();
	pDC->pTask=pTask;
	pDC->pDispatchThread=pTaskThread;
	pDC->pDataBuffer=pDataBuffer;
	pDC->pDataCreator=pDataCreator;
	pTask->m_taskIndex=mp_vecTasks->size();
	mp_vecTasks->push_back(pDC);
	return mp_vecTasks->size()-1;
}

uint32_t MFTaskManager::addTask(
		MFAbstractDataProcessingTask* pTask,
		MFStructurableDataBuffer* pDataBuffer,
		MFTaskThread* pTaskThread){
	DispatchCollection* pDC=new DispatchCollection();
	pDC->pTask=pTask;
	pDC->pDispatchThread=pTaskThread;
	pDC->pDataBuffer=pDataBuffer;
	pDC->pDataCreator=pTask;
	pTask->m_taskIndex=mp_vecTasks->size();
	mp_vecTasks->push_back(pDC);
	return mp_vecTasks->size()-1;
}

uint32_t MFTaskManager::addTask(
		MFAbstractDataProcessingTask* pTask,
		MFStructurableDataBuffer* pTaskDataProvider){
	return addTask(pTask, pTaskDataProvider,nullptr);
}
void MFTaskManager::setDispatchThread(
		MFAbstractTask* pTask,
		MFTaskThread* pDispatchThread){
	if(mp_vecTasks->at(pTask->m_taskIndex)->pTask!=pTask){
		MFObject::printErr("MFTaskManager::setDispatchThread - failed, given task"
				" not contained in dispatch manager!");
		return;
	}
	mp_vecTasks->at(pTask->m_taskIndex)->pDispatchThread=pDispatchThread;
}

void MFTaskManager::setDataBuffer(
		MFAbstractTask* pTask,
		MFStructurableDataBuffer* pDataBuffer){
	if(mp_vecTasks->at(pTask->m_taskIndex)->pTask!=pTask){
		MFObject::printErr("MFTaskManager::setDataBuffer - failed, given task"
				" not contained in dispatch manager!");
		return;
	}
	pDataBuffer->initBuffer();
	mp_vecTasks->at(pTask->m_taskIndex)->pDataBuffer=pDataBuffer;
}

MFAbstractTask* MFTaskManager::getTask(uint16_t taskID){
	if(taskID>=mp_vecTasks->size()){
		MFObject::printWarning("MFTaskManager::getTask - invalid taskID! taskID="
				""+std::to_string(taskID));
		return mp_dummyData->pTask;
	}
	return mp_vecTasks->at(taskID)->pTask;
}
MFTaskThread* MFTaskManager::getTaskThread(
		MFAbstractTask* pTask){
	if(mp_vecTasks->at(pTask->m_taskIndex)->pTask!=pTask){
		MFObject::printErr("MFTaskManager::getTaskThread - failed, given task"
				" not contained in dispatch manager!");
		return nullptr;
	}
	return mp_vecTasks->at(pTask->m_taskIndex)->pDispatchThread;
}

MFStructurableDataBuffer* MFTaskManager::getDataBuffer(MFAbstractTask* pTask){
	if(pTask->m_taskIndex>=mp_vecTasks->size()){
		MFObject::printWarning("MFTaskManager::getDataBuffer - "
				"pTask->m_taskIndex task index out of bounce! index="+
				std::to_string(pTask->m_taskIndex));
		return nullptr;
	}
	if(mp_vecTasks->at(pTask->m_taskIndex)->pTask!=pTask){
		MFObject::printErr("MFTaskManager::getTaskThread - failed, given task"
				" not contained in dispatch manager!");
		return nullptr;
	}
	return mp_vecTasks->at(pTask->m_taskIndex)->pDataBuffer;
}
MFIStructurableDataCreator* MFTaskManager::getDataCreator(MFAbstractTask* pTask){
	if(pTask->m_taskIndex>=mp_vecTasks->size()){
		MFObject::printWarning("MFTaskManager::getDataBuffer - "
				"pTask->m_taskIndex task index out of bounce! index="+
				std::to_string(pTask->m_taskIndex));
		return nullptr;
	}
	if(mp_vecTasks->at(pTask->m_taskIndex)->pTask!=pTask){
		MFObject::printErr("MFTaskManager::getTaskThread - failed, given task"
				" not contained in dispatch manager!");
		return nullptr;
	}
	return mp_vecTasks->at(pTask->m_taskIndex)->pDataCreator;
}

