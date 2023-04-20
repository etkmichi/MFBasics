/*
 * MFStructurableData.cpp
 *
 *  Created on: 17.03.2020
 *      Author: michl
 */

#include "MFStructurableData.h"
#include "../MFObjects/MFObject.h"
#include <string.h>
#include <exception>
#include "../MFBasicDefines.h"

MFStructurableData::MFStructurableData() {
  mp_vecDataCollection=new std::vector<MFDataObject*>();
  mp_vecInternalData=new std::vector<MFDataObject*>();
}

MFStructurableData::~MFStructurableData() {
  clear();
  delete mp_vecDataCollection;
  delete mp_vecInternalData;
}

void MFStructurableData::setupSharedBufferData(MFDataObject* pData){
  if(mp_sharedBuffer!=nullptr && pData!=nullptr){
    if(!mp_sharedBuffer->setupDataObject(pData)){
      MFObject::printErr("MFStructurableData::setupSharedBufferData - "
          "failed to setup data "
          "within shared buffer!");
    }
  }
}

MFDataObject* MFStructurableData::addData(MFDataObject &typeInfo){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);
  pData->setGuiType((E_GuiElement)typeInfo.getGuiType());
  pData->setDataType((E_DataType)typeInfo.getDataType());
  pData->setNBitSize(typeInfo.getNBitSize());
  pData->setDataByteSize(typeInfo.getDataSize());
  pData->setData(typeInfo.getData());
  mp_vecDataCollection->push_back(pData);
  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

void MFStructurableData::addData(MFDataObject* pData,bool deleteByDestructor){
  mp_vecDataCollection->push_back(pData);
  if(deleteByDestructor)mp_vecInternalData->push_back(pData);
  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return;
}

void MFStructurableData::importDataStructure(MFStructurableData* pExternalData){
  clear();
  for(MFDataObject* pDO:*pExternalData->getVecData()){
    addData(*pDO);
  }
}

void MFStructurableData::appendDataStructure(
    MFStructurableData* pExternalData){
  for(MFDataObject* pDO:*pExternalData->getVecData()){
    addData(*pDO);
  }
}
MFDataObject* MFStructurableData::add3DVec(void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);
  pData->setGuiType(GUI_TYPE_3D_VEC);
  pData->setDataType(DATA_TYPE_VEC_3D);
  pData->setData(data);
  mp_vecDataCollection->push_back(pData);
  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add4x4Matrix(void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_MATRIX);
  pData->setDataType(DATA_TYPE_MAT_4X4);
  pData->setData(data);
  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add2DVec(void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_2D_VEC);
  pData->setDataType(DATA_TYPE_VEC_2D);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add64BitValue(E_DataType subType,void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_NUMBER_VIEW);
  pData->setDataType(subType);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}
MFDataObject* MFStructurableData::add64BitDataPointer(void** data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_DATA_POINTER);
  pData->setDataType(DATA_TYPE_VOID_PTR_64);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add32BitValue(E_DataType subType,void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_NUMBER_VIEW);
  pData->setDataType(subType);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add16BitValue(E_DataType subType,void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_NUMBER_VIEW);
  pData->setDataType(subType);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);
  m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::add8BitValue(E_DataType subType,void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_NUMBER_VIEW);
  pData->setDataType(subType);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=pData->getDataSize();
  return pData;
}

MFDataObject* MFStructurableData::addNBitValue(uint32_t bitCount,void* data){
  MFDataObject *pData=new MFDataObject();
  mp_vecInternalData->push_back(pData);

  pData->setGuiType(GUI_TYPE_BIT_VIEW);
  pData->setNBitSize(bitCount);
  pData->setDataByteSize(bitCount/8);
  pData->setDataType(DATA_TYPE_N_BIT);
  pData->setData(data);

  mp_vecDataCollection->push_back(pData);

  setupSharedBufferData(pData);m_dataSize+=bitCount/8;
  return pData;
}

void MFStructurableData::clear(){
  //TODO what if data was used with shared buffer? -> invalidate shared buffer?
  for(MFDataObject* pData:*mp_vecInternalData)delete pData;
  mp_vecDataCollection->clear();
  mp_vecInternalData->clear();
  setStructureSize(0);
}

bool MFStructurableData::copyDataToStructure(void* src_buffer,uint32_t src_offset){
  uint8_t* src=(uint8_t*)src_buffer;
  src+=src_offset;
  bool ret=true;
  if(mp_sharedBuffer!=nullptr){
    void* dataDst=mp_vecDataCollection->at(0)->getData();
    try{
      if(dataDst==nullptr){
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "no input data!");
        return false;
      }
      memcpy(dataDst,src,m_dataSize);
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
    return ret;
  }
  for(MFDataObject* pData:*mp_vecDataCollection){
    try{
      if(pData==nullptr){
        MFObject::printErr("MFStructurableData::writeDataToBuffer - failed,"
            "one data pointer of the collection is nullptr!");
        ret=false;
        continue;
      }
      void* dataDst=pData->getData();
      uint32_t dataInSize=pData->getDataSize();
      if(dataDst==nullptr){
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "dst data dataDst==nullptr !");
        continue;
      }
      memcpy(dataDst,src,dataInSize);
      src+=dataInSize;
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
  }
  return ret;
}

bool MFStructurableData::copyDataToStructure(
    void* src_buffer,
    uint32_t src_offset,
    uint32_t length){
  uint8_t* src=(uint8_t*)src_buffer;
  src+=src_offset;
  bool ret=true;
  if(length>m_dataSize){
    MFObject::printErr("MFStructurableData::copyDataToBuffer - length>m_dataSize");
    return false;
  }
  if(mp_sharedBuffer!=nullptr){
    void* dataDst=mp_vecDataCollection->at(0)->getData();
    try{
      if(dataDst==nullptr){
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "no input data!");
        return false;
      }
      memcpy(dataDst,src,length);
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
    return ret;
  }
  uint32_t remainingData=length;
  for(MFDataObject* pData:*mp_vecDataCollection){
    try{
      if(pData==nullptr){
        MFObject::printErr("MFStructurableData::writeDataToBuffer - failed,"
            "one data pointer of the collection is nullptr!");
        ret=false;
        continue;
      }
      void* dataDst=pData->getData();
      if(remainingData<pData->getDataSize()){
        if(remainingData>0){
          MFObject::printWarning("MFStructurableData::copyDataToBuffer - "
              "data fragment not matching remaining buffer object!!");
          memcpy(dataDst,src,remainingData);
        }
        return ret;
      }
      uint32_t dataInSize=pData->getDataSize();
      if(dataDst==nullptr){
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "dst data dataDst==nullptr !");
        continue;
      }
      memcpy(dataDst,src,dataInSize);
      src+=dataInSize;
      remainingData-=dataInSize;
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
  }
  return ret;
}

void* MFStructurableData::getStructureData(){
//    if(mp_sharedBuffer==nullptr){
//      MFObject::printWarning("MFStructurableData::getStructureData() - "
//          "the returned pointer must only be used for the first "
//          "data entry! Data was not set up with shared buffer!");
//    }
  if(mp_vecDataCollection==nullptr){
    P_ERR("mp_vecDataCollection==nullptr -> this must not/cant happen! data was overwritten!");
  }
  if(mp_vecDataCollection->size()==0){
    MFObject::printErr("MFStructurableData::getStructureData - no data setup!");
    return nullptr;
  }
  return mp_vecDataCollection->at(0)->getData();
}

//void MFStructurableData::freeData(){
//  for(MFDataObject* pDO:*getVecData()){
//    pDO->freeData();
//  }
//}
bool MFStructurableData::copyDataFromStructure(void* dst_buffer,uint32_t dst_offset){
  uint8_t* dst=(uint8_t*)dst_buffer;
  dst+=dst_offset;
  bool ret=true;
  if(mp_sharedBuffer!=nullptr){
    void* dataIn=mp_vecDataCollection->at(0)->getData();
    try{
      if(dataIn==nullptr){
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "no input data!");
        return false;
      }
      memcpy(dst,dataIn,m_dataSize);
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
    return ret;
  }
  for(MFDataObject* pData:*mp_vecDataCollection){
    try{
      if(pData==nullptr){
        MFObject::printErr("MFStructurableData::writeDataToBuffer - failed,"
            "one data pointer of the collection is nullptr!");
        ret=false;
        continue;
      }
      void* dataIn=pData->getData();
      uint32_t dataInSize=pData->getDataSize();
      bool deleteMem=false;
      if(dataIn==nullptr){
        //TODO thats not ok!
        MFObject::printWarning("MFStructurableData::writeDataToBuffer - "
            "no input data!");
        dataIn=malloc(dataInSize);
        deleteMem=true;
      }
      memcpy(dst,dataIn,dataInSize);
      if(deleteMem){
        free(dataIn);
      }
      dst+=dataInSize;
    }catch (std::exception &e) {
      MFObject::printErr("MFStructurableData::writeDataToBuffer - "
          "failed to copy data! Exception caught:\n"+
          std::string(e.what()));
      ret = false;
    }
  }
  return ret;
}

void MFStructurableData::useSharedBuffer(MFDataObjectBuffer* pSharedBuffer){
  if(pSharedBuffer==mp_sharedBuffer){
    return;
  }
  mp_sharedBuffer=pSharedBuffer;
  if(pSharedBuffer==nullptr){
    return;
  }
  for(MFDataObject* pData:*mp_vecDataCollection){
    /*If data was set up already*/
    if(pData->getData()!=nullptr){
      MFObject::printWarning("MFStructurableData::useSharedBuffer - data was "
          "\nadded already! data pointer of sub data is not nullptr! The data"
          "\npointer of sub data will be overwritten, take care to update"
          "\nall objects which are using this data!!!");
    }
    mp_sharedBuffer->setupDataObject(pData);
  }
}

void MFStructurableData::printMetaData(){
  std::string info="Data info:\n";
  for(MFDataObject* pDO:*mp_vecDataCollection){
    info+=pDO->toString()+"\n";
  }
  MFObject::printInfo(info);
  return;
}

uint32_t MFStructurableData::calculateStructureSize(){
  uint32_t size=0;
  for(MFDataObject* pData:*mp_vecDataCollection){
    size+=pData->getDataSize();
  }
  m_dataSize=size;
  return size;
}
