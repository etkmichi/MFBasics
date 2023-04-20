/*
 * MFStructurableDataBuffer.cpp
 *
 *  Created on: 20.03.2020
 *      Author: michl
 */

#include "MFStructurableDataBuffer.h"
#include "../MFObjects/MFObject.h"
#include <memory.h>
#include <exception>

MFStructurableDataBuffer::MFStructurableDataBuffer(
		MFIStructurableDataCreator* pDataCreator,
		uint32_t objectCount) {
	if(objectCount>(0xFFFFFFFF/2))
		MFObject::printErr("MFStructurableDataBuffer::MFStructurableDataBuffer - "
				"object count must be less than (0xFFFFFFFF/2)");
	m_objectCount=objectCount;
	mp_dataCreator=pDataCreator;
	mp_vecAvailableBuffers=new std::vector<MFStructurableData*>();
	mp_vecCreatedBuffers=new std::vector<MFStructurableData*>();
	mp_sharedDataBuffer=nullptr;
	mp_baseStructure=mp_dataCreator->createNewEmptyData();
	mp_baseStructure->initData();//needed for m_bufferSize
	mp_dummyBuffer=mp_dataCreator->createNewEmptyData();
	mp_dummyBuffer->initData();
	m_bufferSize=mp_baseStructure->calculateStructureSize()*m_objectCount;
	mp_sharedDataBuffer=new MFDataObjectBuffer(m_bufferSize);
}

MFStructurableDataBuffer::MFStructurableDataBuffer(
		MFStructurableData* pBaseStructure,
		uint32_t objectCount) {
	if(objectCount>(0xFFFFFFFF/2))
		MFObject::printErr("MFStructurableDataBuffer::MFStructurableDataBuffer - "
				"object count must be less than (0xFFFFFFFF/2)");
	m_objectCount=objectCount;
	mp_vecAvailableBuffers=new std::vector<MFStructurableData*>();
	mp_vecCreatedBuffers=new std::vector<MFStructurableData*>();
	mp_baseStructure=pBaseStructure;
	mp_dataCreator=this;
	m_bufferSize=mp_baseStructure->getStructureSize()*m_objectCount;
	mp_sharedDataBuffer=nullptr;

	/*create a copy of the base structure this->createNew...*/
	mp_baseStructure=this->createNewEmptyData();
	mp_baseStructure->initData();

	mp_dummyBuffer=this->createNewEmptyData();
	mp_dummyBuffer->initData();

	/*create the shared buffer*/
	mp_sharedDataBuffer=new MFDataObjectBuffer(m_bufferSize);
}

MFStructurableData* MFStructurableDataBuffer::createNewEmptyData(){
	MFStructurableData* pDS=new MFStructurableData();
	pDS->m_printInitData=false;
	pDS->useSharedBuffer(mp_sharedDataBuffer);
	pDS->importDataStructure(mp_baseStructure);
	return pDS;
}

MFStructurableDataBuffer::~MFStructurableDataBuffer() {
	for(MFStructurableData* pDat:*mp_vecCreatedBuffers){
		delete pDat;
	}
	delete mp_vecCreatedBuffers;
	delete mp_vecAvailableBuffers;
	delete mp_baseStructure;
	delete mp_dummyBuffer;
	delete mp_sharedDataBuffer;
}

bool MFStructurableDataBuffer::initBuffer(){
	if(m_isInitialized){
		MFObject::printWarning("MFStructurableDataBuffer::initBuffer() - "
				"buffer already initialized!");
		return true;
	}

	bool ret=mp_sharedDataBuffer->createBuffer();
	if(!ret){
		MFObject::printErr("MFStructurableDataBuffer::initBuffer() - "
				"failed to init buffer");
		return false;
	}

	for(uint32_t i=0;i<m_objectCount;i++){
		MFStructurableData* pDat=mp_dataCreator->createNewEmptyData();
		pDat->useSharedBuffer(mp_sharedDataBuffer);
		pDat->initData();
		pDat->initDataPointer();
		mp_vecAvailableBuffers->push_back(pDat);
		mp_vecCreatedBuffers->push_back(pDat);
	}
	m_currentIndex=m_objectCount-1;
	m_isInitialized=true;

	return ret;
}

void MFStructurableDataBuffer::fillAll(uint32_t fill){
  lockVecAvailableBuffers.lock();
  for(MFStructurableData* pD:*mp_vecAvailableBuffers){
    memset(pD->getStructureData(),fill,pD->getStructureSize());
  }
  lockVecAvailableBuffers.unlock();
}

MFStructurableData* MFStructurableDataBuffer::takeData(){
	MFStructurableData* pDat=nullptr;
	lockVecAvailableBuffers.lock();
	if(m_currentIndex<0){
		lockVecAvailableBuffers.unlock();
		MFObject::printWarning("MFStructurableDataBuffer::takeData() - "
				"no buffer available! returning dummy buffer! data operations"
				"on this buffer will be invalid!");
		return nullptr;
	}
	pDat=mp_vecAvailableBuffers->at(m_currentIndex);
	m_currentIndex--;
	lockVecAvailableBuffers.unlock();
	return pDat;
}

uint32_t MFStructurableDataBuffer::getAvailableBufferCount(){
	uint32_t count=0;
	lockVecAvailableBuffers.lock();
	count=m_currentIndex+1;
	lockVecAvailableBuffers.unlock();
	return count;
}

uint32_t MFStructurableDataBuffer::getMaxBufferCount(){
	return mp_vecCreatedBuffers->size();
}

bool MFStructurableDataBuffer::returnData(MFStructurableData* pData){
	//TODO multiple usage of structurable data (counter for processing tasks or
	//sth like this) - some data may be needed for multiple tasks...
	//TODO check data pointers to ensure that buffer is within the initialized range!
	lockVecAvailableBuffers.lock();
	if(pData==mp_dummyBuffer){
		MFObject::printWarning("MFStructurableDataBuffer::returnData - dummy buffer "
				"was return! Invalid data opperations occured!!!");
		lockVecAvailableBuffers.unlock();
		return false;
	}
	if(m_currentIndex>=((int32_t)m_objectCount-1)){
		MFObject::printErr("MFStructurableDataBuffer::returnData - "
				"buffer overflow, invalid data return!");
		lockVecAvailableBuffers.unlock();
		return false;
	}
	m_currentIndex++;
	mp_vecAvailableBuffers->data()[m_currentIndex]=pData;
	lockVecAvailableBuffers.unlock();
	return true;
}
