/*
 * MFDeletionTask.cpp
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#include "MFDeletionTask.h"
#include "../MFTime/MFTickCounter.h"
MFDeletionTask::MFDeletionTask() {
	m_nextDeletionTime=0;
}

MFDeletionTask::~MFDeletionTask() {
}

void MFDeletionTask::prepareInputData(MFStructurableData* pData){
	/*this function checks the timepoi*/
	int64_t
		now=MFTickCounter::current(),
		delTimePoint=*((int64_t*)(pData->getVecData()->at(1)->getData()));
	if(m_nextDeletionTime==0){
		m_nextDeletionTime=delTimePoint;
	}
	if(delTimePoint<now){
		if(mp_wakableThread!=nullptr)
			mp_wakableThread->wakeUp();
		return;
	}
	if(delTimePoint<m_nextDeletionTime){
		m_nextDeletionTime=delTimePoint;
	}
}

bool MFDeletionTask::processData(MFStructurableData* pData){
	//check time
	void*
		maybeDeletable=*((void**)(pData->getVecData()->at(0)->getData()));

	int64_t
		delTimePoint=*((int64_t*)(pData->getVecData()->at(1)->getData()));

	U_TimePoint
		tpNow=U_Clock::now(),
		tpDelTime=U_TimePoint(U_ClockDuration(delTimePoint));

	time_t
		tNow=U_Clock::to_time_t(tpNow),
		tDel=U_Clock::to_time_t(tpDelTime);

	if(m_nextDeletionTime==0){
		m_nextDeletionTime=delTimePoint;
	}
	if(tpNow>=tpDelTime){
		MFObject::printWarning("Now>DelTime: "+
				std::string(std::ctime(&tNow))+" > "+
				std::string(std::ctime(&tDel)));
		if(maybeDeletable!=nullptr){
			free(maybeDeletable);
			MFObject::printWarning("DEBUG - data was freed!");
		}else{
			MFObject::printWarning("DEBUG - data was nullptr!");
		}
		void* ow=nullptr;
		pData->getVecData()->at(0)->writeData(&ow);
	}else{
		MFObject::printWarning("Now<DelTime: "+
				std::string(std::ctime(&tNow))+" < "+
				std::string(std::ctime(&tDel)));
		if(delTimePoint<m_nextDeletionTime){
			m_nextDeletionTime=delTimePoint;
		}
		addInputData(pData,false);
		MFObject::printWarning("DEBUG - reenqueued for deletion");
		return false;
	}
	return true;
}
