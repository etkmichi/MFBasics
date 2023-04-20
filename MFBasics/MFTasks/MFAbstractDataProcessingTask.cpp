/*
 * MFAbstractDataProcessingTask.cpp
 *
 *  Created on: 19.03.2020
 *      Author: michl
 */

#include "MFAbstractDataProcessingTask.h"

MFAbstractDataProcessingTask::MFAbstractDataProcessingTask() {
	mp_vecInputData=new std::vector<MFStructurableData*>();
	mp_vecProcessingData=new std::vector<MFStructurableData*>();
	mp_dummyData=new MFStructurableData();
	mp_bufferSink=nullptr;
	mp_wakableThread=nullptr;
	mp_externalDataCreator=nullptr;
}

MFAbstractDataProcessingTask::~MFAbstractDataProcessingTask() {
}

void MFAbstractDataProcessingTask::addInputData(
		MFStructurableData* pInputData,
		bool prepareInput){
	if(prepareInput)prepareInputData(pInputData);
	lockVecInput.lock();
	mp_vecInputData->push_back(pInputData);
	lockVecInput.unlock();
}

bool MFAbstractDataProcessingTask::doWork(){
	/*TODO make thread safe, use two input buffer and switch between them*/
	std::vector<MFStructurableData*>* pVec=nullptr;
	lockVecInput.lock();
	lockVecProcessingData.lock();
	pVec=mp_vecInputData;
	mp_vecInputData=mp_vecProcessingData;
	mp_vecProcessingData=pVec;
	lockVecInput.unlock();
	bool failure=false;
	bool ret;
	for(MFStructurableData* pSD:*mp_vecProcessingData){
		ret=processData(pSD);
//		try{TODO
//			ret=processData(pSD);
//		}catch(std::exception& e){
//			ret=false;
//			failure=true;
//			MFObject::printErr("MFAbstractDataProcessingTask::doWork exception caught during"
//					"data processing:\n"+std::string(e.what()));
//		}
		if(!ret && m_enableReprocessing){
			addInputData(pSD);//TODO what if a lot of data will be requeued?
			continue;
		}
		if(ret && mp_bufferSink!=nullptr){
			if(!mp_bufferSink->returnData(pSD)){
				MFObject::printWarning(" MFAbstractDataProcessingTask::doWork - returning data"
						" to sink failed!");
			}
		}
	}
	postProcessing();
	mp_vecProcessingData->clear();
	lockVecProcessingData.unlock();
	return !failure;
}
