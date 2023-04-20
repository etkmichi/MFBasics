/*
 * MFDataDeletion.cpp
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#include "MFDataDeletion.h"
#include "../MFObjects/MFObject.h"

MFStructurableDataBuffer* MFDataDeletion::smp_bufferProvider=nullptr;
uint32_t MFDataDeletion::sm_maxDeletableObjects=100;
MFDeletionTask* MFDataDeletion::smp_dataDeletionTask=nullptr;
MFDataDeleterThread* MFDataDeletion::smp_deletionThread=nullptr;
std::mutex MFDataDeletion::sm_lockBuffer;

MFDataDeletion::MFDataDeletion() {

}

MFDataDeletion::~MFDataDeletion() {
	// TODO Auto-generated destructor stub
}

void MFDataDeletion::initStaticDataDeletion(){
	sm_lockBuffer.lock();
	MFDataObject::initDataSizes();
	if(smp_bufferProvider==nullptr){
		MFStructurableData* pBaseStructure=new MFStructurableData();
		pBaseStructure->add64BitDataPointer(nullptr);
		pBaseStructure->addData((int64_t*)nullptr);
		smp_bufferProvider=new MFStructurableDataBuffer(
				pBaseStructure,
				sm_maxDeletableObjects);
		uint32_t dataSize=(sm_maxDeletableObjects*pBaseStructure->getStructureSize());
		MFObject::printWarning("MFDataDeletion::initStaticDataDeletion() static "
				"allocation of "+std::to_string(dataSize)+" bytes!");
		smp_bufferProvider->initBuffer();
		delete pBaseStructure;
	}
	if(smp_deletionThread==nullptr){
		smp_deletionThread=new MFDataDeleterThread();
		smp_deletionThread->setPauseTime(3000000000, true);
	}
	if(smp_dataDeletionTask==nullptr){
		smp_dataDeletionTask=new MFDeletionTask();
		smp_deletionThread->setDeletionTask(smp_dataDeletionTask);
		smp_dataDeletionTask->setBufferSink(smp_bufferProvider);
		smp_dataDeletionTask->setWakeableThread(smp_deletionThread);
	}
	sm_lockBuffer.unlock();
}

bool MFDataDeletion::addData(void* data,int64_t timeTillDeletion){
	if(smp_bufferProvider==nullptr){
		MFObject::printErr("MFDataDeletion::addData - static deletion not initialized!");
		return false;
	}
	MFStructurableData* pDel=smp_bufferProvider->
			takeData();
//	int64_t delTimePoint=(MFTickCounter::current())+timeTillDeletion;
	U_TimePoint tp=U_Clock::now()+
			U_ClockDuration(timeTillDeletion);
	int64_t tpC=tp.time_since_epoch().count();
	pDel->getVecData()->at(0)->writeData(&data);
	pDel->getVecData()->at(1)->writeData(&(tpC));
	smp_dataDeletionTask->addInputData(pDel);
	smp_deletionThread->addTask(smp_dataDeletionTask);
	std::time_t tnow=U_Clock::to_time_t(U_Clock::now());
	std::time_t t=U_Clock::to_time_t(tp);
	std::string timeInfos="";
	timeInfos+="\ntime now: "+std::string(std::ctime(&tnow));
	timeInfos+="\ntime del: "+std::string(std::ctime(&t));
	MFObject::printInfo("Debug MFDataDeletion::addData - time infos:"+timeInfos);
	return true;
}
