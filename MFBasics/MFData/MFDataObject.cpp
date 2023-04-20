/*
 * MFDataObject.cpp
 *
 *  Created on: 03.12.2019
 *      Author: michl
 */
#include <cstring>
#include "MFDataObject.h"
#include "../MFObjects/MFObject.h"

std::vector<uint32_t>* MFDataObject::smp_vecDataSizes=new std::vector<uint32_t>();
std::mutex MFDataObject::lockVecTypes;

MFDataObject::MFDataObject()
{
	initDataSizes();
	m_subDataType=DATA_TYPE_DUMMY;
	m_dataType=DATA_TYPE_DUMMY;
	m_guiType=GUI_TYPE_NONE;
	m_subGuiType=GUI_TYPE_NONE;
	m_dataByteSize=0;
	mp_externalUsage=new std::mutex();
	mp_data=nullptr;
}

void MFDataObject::initDataSizes(){
	lockVecTypes.lock();
	if(smp_vecDataSizes->size()==0){
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_DUMMY]	=64;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_BOOL]	=1;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_UINT8]	=1;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_UINT16] = 2;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_UINT32] = 4;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_UINT64] = 8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_INT8]	= 1;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_INT16]	= 2;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_INT32]	= 4;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_INT64]	= 8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_FLOAT32]	= 4;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_DOUBLE64]	= 8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_VOID_PTR_64]	= 8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_VEC_2D]	= 8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_VEC_3D]	=12;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_VEC_4D]	=16;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_N_VEC_2D]	=8;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_N_VEC_3D]	=12;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_N_VEC_4D]	=16;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_MAT_3X3]	=36;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_MAT_4X4]	=64;
		MFObject::printInfo(std::to_string(DATA_TYPE_MAT_4X4));
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_N_MAT_4X4]=64;
		smp_vecDataSizes->push_back(0);
		smp_vecDataSizes->data()[DATA_TYPE_STRING]	=64;

		/*this type must be the last entry!*/
		smp_vecDataSizes->push_back(0);
		while(smp_vecDataSizes->size()-1<DATA_TYPE_N_BIT){
			smp_vecDataSizes->push_back(0);
		}
		smp_vecDataSizes->data()[DATA_TYPE_N_BIT]= 1;
	}
	lockVecTypes.unlock();
}

MFDataObject::~MFDataObject() {
	if(mp_innerData!=nullptr)
		free(mp_innerData);
}
//void MFDataObject::freeData(){
//  if(mp_innerData==mp_data){
//    free(mp_innerData);
//    mp_innerData=nullptr;
//    return;
//  }
//  if(mp_innerData)free(mp_innerData);
//  if(mp_data)free(mp_data);
//  mp_data=nullptr;
//  mp_innerData=nullptr;
//}

void MFDataObject::setDataType(E_DataType type){
	m_dataType=type;
	if(DATA_TYPE_N_BIT==type){
		m_dataByteSize=(m_nBitSize/8);
		return;
	}
	if(type<smp_vecDataSizes->size()-1){
		m_dataByteSize=smp_vecDataSizes->data()[type];
	}else{
		MFObject::printWarning("MFDataObject::setDataType - "
				"no size found for given type!");
	}
}

void MFDataObject::setSubDataType(E_DataType type){
	m_subDataType=type;
}
uint32_t MFDataObject::getSizeOfType(){
	if(m_dataType<smp_vecDataSizes->size()){
		return smp_vecDataSizes->at(m_dataType);
	}
	MFObject::printErr("MFDataObject::getSizeOfType() - "
			"No valid size for type found! returning 0!");
	return 0;
}

void MFDataObject::setDataTypeSize(E_DataType dataType,uint32_t size){
	lockVecTypes.lock();
	if(dataType<smp_vecDataSizes->size()){
		smp_vecDataSizes->data()[dataType]=size;
	}else{
		MFObject::printErr("static MFDataObject::setDataTypeSize - "
				"no size entry for this type!");
	}
	lockVecTypes.unlock();
}

void MFDataObject::lockExternalUsage(){
	mp_externalUsage->lock();
}
void MFDataObject::unlockExternalUsage(){
	mp_externalUsage->unlock();
}

bool MFDataObject::writeData(void* data,const uint32_t &sizeCheck){
	if(mp_writeDataInterface!=nullptr){
		return mp_writeDataInterface->writeData(mp_data,data,sizeCheck);
	}
	if(!m_writable){
		MFObject::printErr("MFDataObject::writeData - data not writable!!");
		return false;
	}
	if(sizeCheck>m_dataByteSize){
		MFObject::printErr("MFDataObject::writeData - size doesnt match! "
				"sizeCheck!=m_dataByteSize : "+
				std::to_string(sizeCheck)+":"+std::to_string(m_dataByteSize));
		return false;
	}
	if(mp_data==nullptr){
		MFObject::printWarning("MFDataObject::writeData - allocated data for writing!"
				" The data will be deleted in destructor!");
		mp_innerData=malloc(m_dataByteSize);
	}
	try{
		memcpy(mp_data,data,sizeCheck);
	}catch(std::exception &e){
		MFObject::printErr("MFDataObject::writeData - failed to copy data: "+
				std::string(e.what()));
		return false;
	}
	return true;
}

bool MFDataObject::writeData(const void* data,const uint32_t &sizeCheck){
        if(mp_writeDataInterface!=nullptr){
                mp_writeDataInterface->writeData(mp_data,data,sizeCheck);
        }
        if(!m_writable){
                MFObject::printErr("MFDataObject::writeData - data not writable!!");
                return false;
        }
        if(sizeCheck>m_dataByteSize){
                MFObject::printErr("MFDataObject::writeData - size doesnt match! "
                                "sizeCheck!=m_dataByteSize : "+
                                std::to_string(sizeCheck)+":"+std::to_string(m_dataByteSize));
                return false;
        }
        if(mp_data==nullptr){
                MFObject::printWarning("MFDataObject::writeData - allocated data for writing!"
                                " The data will be deleted in destructor!");
                mp_innerData=malloc(m_dataByteSize);
        }
        try{
                memcpy(mp_data,data,sizeCheck);
        }catch(std::exception &e){
                MFObject::printErr("MFDataObject::writeData - failed to copy data: "+
                                std::string(e.what()));
                return false;
        }
        return true;
}
std::string MFDataObject::toString(){
	std::string ret="MFDataObject::toString() ";
	float* pFloatData=((float*)mp_data);
	uint32_t* dataPtr=(uint32_t*)mp_data;
	switch(m_dataType){
	case DATA_TYPE_BOOL:
		ret+=std::string("DATA_TYPE_BOOL: ")+std::to_string(*((bool*)mp_data));
		break;
	case DATA_TYPE_DUMMY:
		ret+=std::string("DATA_TYPE_DUMMY: ")+"-";
		break;
	case DATA_TYPE_UINT8:
		ret+=std::string("DATA_TYPE_UINT8: ")+std::to_string(*((uint8_t*)mp_data));
		break;
	case
		DATA_TYPE_UINT16:
		ret+=std::string("DATA_TYPE_UINT16: ")+std::to_string(*((uint16_t*)mp_data));
		break;
	case DATA_TYPE_UINT32:
		ret+=std::string("DATA_TYPE_UINT32: ")+std::to_string(*((uint32_t*)mp_data));
		break;
	case DATA_TYPE_UINT64:
		ret+=std::string("DATA_TYPE_UINT64: ")+std::to_string(*((uint64_t*)mp_data));
		break;
	case DATA_TYPE_INT8:
		ret+=std::string("DATA_TYPE_INT8: ")+std::to_string(*((int8_t*)mp_data));
		break;
	case DATA_TYPE_INT16:
		ret+=std::string("DATA_TYPE_INT16: ")+std::to_string(*((int16_t*)mp_data));
		break;
	case DATA_TYPE_INT32:
		ret+=std::string("DATA_TYPE_INT32: ")+std::to_string(*((int32_t*)mp_data));
		break;
	case DATA_TYPE_INT64:
		ret+=std::string("DATA_TYPE_INT64: ")+std::to_string(*((int64_t*)mp_data));
		break;
	case DATA_TYPE_FLOAT32:
		ret+=std::string("DATA_TYPE_FLOAT32: ")+std::to_string(*((float*)mp_data));
		break;
	case DATA_TYPE_DOUBLE64:
		ret+=std::string("DATA_TYPE_DOUBLE64: ")+std::to_string(*((double*)mp_data));
		break;
	case DATA_TYPE_VOID_PTR_64:
		ret+=std::string("DATA_TYPE_VOID_PTR_64: ")+std::to_string(*((double*)mp_data));
		break;
	case DATA_TYPE_VEC_2D:
	case DATA_TYPE_N_VEC_2D:
		ret+=std::string("DATA_TYPE_N_VEC_2D: ");
		for(uint32_t offset=0;offset<2;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_VEC_3D:
		ret+=std::string("DATA_TYPE_N_VEC_3D: ");
		for(uint32_t offset=0;offset<3;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_N_VEC_3D:
		ret+=std::string("DATA_TYPE_N_VEC_3D: ");
		for(uint32_t offset=0;offset<3;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_VEC_4D:
		ret+=std::string("DATA_TYPE_N_VEC_4D: ");
		for(uint32_t offset=0;offset<4;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_N_VEC_4D:
		ret+=std::string("DATA_TYPE_N_VEC_4D: ");
		for(uint32_t offset=0;offset<4;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_MAT_3X3:
		ret+=std::string("DATA_TYPE_MAT_3X3: ");
		for(uint32_t offset=0;offset<9;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_MAT_4X4:
		ret+=std::string("DATA_TYPE_MAT_4X4: ");
		for(uint32_t offset=0;offset<16;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_N_MAT_4X4:
		ret+=std::string("DATA_TYPE_N_MAT_4X4: ");
		for(uint32_t offset=0;offset<16;offset++){
			if(offset%4==0)ret+="\n";
			ret+=std::to_string(*(pFloatData+offset))+" ";
		}
		break;
	case DATA_TYPE_N_BIT:
		ret+=std::string("DATA_TYPE_N_BIT: \n");
		for(uint32_t i=1000;i<(1000+m_dataByteSize);i++){
			if((i+1)%8==0){
				ret+="\t"+std::to_string(i)+": "+std::to_string(
						(*dataPtr)+1000000000)+"\n";
			}else{
				ret+="\t"+std::to_string(i)+": "+std::to_string(
						(*dataPtr)+1000000000)+" - ";
			}
			dataPtr++;
		}
		break;

	case DATA_TYPE_STRING:
		ret+=std::string("DATA_TYPE_STRING: ")+(*((std::string*)mp_data));
		break;
	default:
		ret+="no default implementaiton!";
	}
	return ret;
}

bool MFDataObject::writeData(void* data){
  if(mp_writeDataInterface!=nullptr){
    return mp_writeDataInterface->writeData(
        mp_data,data,m_dataByteSize);
  }
	if(!m_writable){
		MFObject::printErr("MFDataObject::writeData - data not writable!!");
		return false;
	}
	if(mp_data==nullptr){
		MFObject::printWarning("MFDataObject::writeData - allocated data for writing!"
				" The data will be deleted in destructor! object name:"+m_objectName);
		mp_innerData=malloc(m_dataByteSize);
		mp_data=mp_innerData;
	}
	try{
		memcpy(mp_data,data,m_dataByteSize);
	}catch(std::exception &e){
		MFObject::printErr("MFDataObject::writeData - failed to copy data: "+
				std::string(e.what()));
		return false;
	}
	return true;
}

bool MFDataObject::writeData(const void* data){
  if(mp_writeDataInterface!=nullptr){//TODO what if !m_writable==true?
    return mp_writeDataInterface->writeData(
        mp_data,data,m_dataByteSize);
  }
  if(!m_writable){
    MFObject::printErr("MFDataObject::writeData - data not writable!!");
    return false;
  }
  if(mp_data==nullptr){
    MFObject::printWarning("MFDataObject::writeData - allocated data for writing!"
        " The data will be deleted in destructor! object name:"+m_objectName);
    mp_innerData=malloc(m_dataByteSize);
    mp_data=mp_innerData;
  }
  try{
    memcpy(mp_data,data,m_dataByteSize);
  }catch(std::exception &e){
    MFObject::printErr("MFDataObject::writeData - failed to copy data: "+
        std::string(e.what()));
    return false;
  }
  return true;
}

bool MFDataObject::allocate(uint32_t dataSize){
	if(mp_data!=nullptr){
		MFObject::printWarning("MFDataObject::allocate - mp_data!=nullptr!!! Data "
				"of MFDataObject will change, take care to update external usage!");
	}
	if(mp_innerData!=nullptr){
		MFObject::printWarning("MFDataObject::allocate - mp_innerData!=nullptr!!! "
				"Data will not be deleted, take care for possible memory leak! Old data"
		    " will not be freed, because it may be in use by some user programm.");
	}
	if(dataSize!=0)
	  m_dataByteSize=dataSize;
	mp_innerData=malloc(m_dataByteSize);
	mp_data=mp_innerData;
	if(mp_innerData==nullptr){
		MFObject::printErr("MFDataObject::allocate - allocation failed!!!");
	}
	return (mp_innerData!=nullptr);
}
