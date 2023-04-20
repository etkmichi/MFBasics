/*
 * MFDataObjectBuffer.cpp
 *
 *  Created on: 21.02.2020
 *      Author: michl
 */

#include <exception>
#include <cstring>
#include "MFDataObjectBuffer.h"
#include "../MFObjects/MFObject.h"
MFDataObjectBuffer::MFDataObjectBuffer() {
	m_bufferByteSize=0;
	mp_vecDataObjects=new std::vector<MFDataObject*>();
	mp_vecInternalDataObjects=new std::vector<MFDataObject*>();
	mp_vecExternalDataObjects=new std::vector<MFDataObject*>();
	mp_dataObjectBuffer=new MFDataObject();
	mp_dataObjectBuffer->invalidate();
}

MFDataObjectBuffer::MFDataObjectBuffer(uint64_t bufferByteSize) {
	m_bufferByteSize=bufferByteSize;
	mp_vecDataObjects=new std::vector<MFDataObject*>();
	mp_vecInternalDataObjects=new std::vector<MFDataObject*>();
	mp_vecExternalDataObjects=new std::vector<MFDataObject*>();
	mp_dataObjectBuffer=new MFDataObject();
	mp_dataObjectBuffer->setDataByteSize(bufferByteSize);
	mp_dataObjectBuffer->invalidate();
}

MFDataObjectBuffer::~MFDataObjectBuffer() {
	uint32_t index=0;
	for(MFDataObject* pD:*mp_vecInternalDataObjects){
		delete pD;
		mp_vecInternalDataObjects->at(index)=nullptr;
		index++;
	}
	index=0;
	for(MFDataObject* pD:*mp_vecExternalDataObjects){
		pD->invalidate();
		mp_vecInternalDataObjects->at(index)=nullptr;
		index++;
	}
	mp_vecInternalDataObjects->clear();
	mp_dataObjectBuffer->invalidate();
	delete mp_dataObjectBuffer;
	delete mp_vecDataObjects;
	delete mp_vecInternalDataObjects;
	delete mp_vecExternalDataObjects;
	if(mp_internalBuffer!=nullptr)free(mp_internalBuffer);
}

bool MFDataObjectBuffer::createBuffer(){
	if(m_isCreated==true){
		MFObject::printWarning("MFDataObjectBuffer::createBuffer() - "
				"buffer already created!");
		return true;
	}
	if(m_bufferByteSize==0){
		MFObject::printErr("MFDataObjectBuffer::createBuffer - failed, buffer"
				"byte size == 0!");
		return false;
	}
	try{
		if(mp_buffer==nullptr){
			mp_internalBuffer=malloc(m_bufferByteSize);
			mp_buffer=mp_internalBuffer;
		}
	}catch(std::exception &e){
		MFObject::printErr("MFDataObjectBuffer::createBuffer() - failed, "+
				std::string(e.what()));
		m_isCreated=false;
		return false;
	}
	mp_dataObjectBuffer->setData(mp_buffer);
	mp_dataObjectBuffer->setDataByteSize(m_bufferByteSize);
	mp_dataObjectBuffer->validate();
	m_bufferByteOffset=0;
	m_isCreated=true;
	return true;
}

MFDataObject* MFDataObjectBuffer::getNextDataObject(uint64_t byteSize){
	if((m_bufferByteOffset+byteSize)>m_bufferByteSize){
		MFObject::printErr("MFDataObjectBuffer::getNextDataObject - failed to create"
				"object, buffer out of bounce!");
		return nullptr;
	}
	MFDataObject* pDat=new MFDataObject();
	pDat->setDataByteSize(byteSize);
	void* pData=(void*)(((uint8_t*)mp_buffer)+m_bufferByteOffset);
	m_bufferByteOffset+=byteSize;
	pDat->setData(pData);
	mp_vecDataObjects->push_back(pDat);
	mp_vecInternalDataObjects->push_back(pDat);
	return pDat;
}

bool MFDataObjectBuffer::setupDataObject(MFDataObject* dataObject){
	uint64_t dataSize=dataObject->getDataSize();
	lockBuffer.lock();
	if((m_bufferByteOffset+dataSize)>m_bufferByteSize){
		lockBuffer.unlock();
		MFObject::printErr("MFDataObjectBuffer::setupDataObject - failed to create "
				"object, buffer out of bounce!");
		return false;
	}
	if(mp_buffer==nullptr){//TODO check if data was already setup by this buffer...
		lockBuffer.unlock();
		MFObject::printErr("MFDataObjectBuffer::setupDataObject - failed to create "
				"object, mp_buffer==nullptr!");
		return false;
	}
	void* pData=(void*)(((uint8_t*)mp_buffer)+m_bufferByteOffset);
	m_bufferByteOffset+=dataSize;
	dataObject->setData(pData);
	mp_vecDataObjects->push_back(dataObject);
	mp_vecExternalDataObjects->push_back(dataObject);
	lockBuffer.unlock();
	void* copyData=dataObject->getData();
	if(copyData!=nullptr){
		lockBufferWrite.lock();
		memcpy(pData,copyData,dataSize);
		lockBufferWrite.unlock();
	}
	return true;
}
