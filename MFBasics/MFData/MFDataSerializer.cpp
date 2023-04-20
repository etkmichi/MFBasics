/*
 * MFDataSerializer.cpp
 *
 *  Created on: 27.04.2020
 *      Author: michl
 */

#include "MFDataSerializer.h"
#include <memory.h>
#include <vector>

MFDataObject* MFDataSerializer::createSerializedData(
		MFDataObject* pData,
		void* pOutData){
//	MFObject::printInfo("MFDataSerializer::createSerializedData - "
//			"serializing data:\n"+pData->toString());
	void* serializedData=pOutData;//set to returned data object
	uint32_t size=0;
	size+=sizeof(uint32_t);//size of pOutData (allocated data)
	size+=(sizeof(E_DataType));//Type of pData
	size+=(sizeof(E_GuiElement));//Type of gui element

	uint32_t dataSize=pData->getDataSize();
	if(dataSize==0){
		MFObject::printWarning("MFDataSerializer::createSerializedData("
		"MFDataObject* pData - serializing data with size==0! objectName:"+
		pData->getObjectName());
	}
	size+=dataSize;//size of data part

	if(pOutData==nullptr){
		serializedData=malloc(size);
	}
	MFDataObject* pRetData=new MFDataObject();
	pRetData->setDataType(E_DataType::DATA_TYPE_N_BIT);
	pRetData->setDataByteSize(size);
	pRetData->setData(serializedData);

	uint8_t* dstData=(uint8_t*)serializedData;
	memcpy(dstData,&size,sizeof(uint32_t));//cpy oa size
	dstData+=sizeof(uint32_t);

	memcpy(dstData,&pData->getDataType(),sizeof(E_DataType));//cp data type
	dstData+=sizeof(E_DataType);

	memcpy(dstData,&pData->getGuiType(),sizeof(E_GuiElement));//cpy gui type
	dstData+=sizeof(E_GuiElement);

	void* pInData=pData->getData();
	if(pInData==nullptr){
		MFObject::printWarning("MFDataSerializer::createSerializedData(MFDataObject*... - "
				"data of pData == nullptr! objectName:"+
		pData->getObjectName());
	}
	if(pInData!=nullptr)memcpy(dstData,pInData,dataSize);
	return pRetData;
}

MFDataObject* MFDataSerializer::createSerializedData(
		MFStructurableData* pData,
		void* pOutData){
	//|DataSize|DataCount|Data1Header|Data1|Data2Header...
	std::vector<MFDataObject*> *pVecData=pData->getVecData();
	uint32_t dataSize=0;
	uint32_t dataCount=pVecData->size();
	dataSize+=sizeof(uint32_t);//serialized data size
	dataSize+=sizeof(uint32_t);//data counter
	dataSize+=(dataCount*getHeaderDataSize());//headers-size for sub data of pData
	dataSize+=pData->getStructureSize();//data data size
	void* serializedData=pOutData;
	if(serializedData==nullptr){
		serializedData=malloc(dataSize);
	}
	uint8_t* currentData=(uint8_t*)serializedData;

	memcpy(currentData,&dataSize,sizeof(uint32_t));
	currentData+=sizeof(uint32_t);
	memcpy(currentData,&dataCount,sizeof(uint32_t));
	currentData+=sizeof(uint32_t);

	MFDataObject* pCopy=nullptr;
	for(MFDataObject* pDO:*pVecData){
		pCopy=createSerializedData(pDO, currentData);
		currentData+=pCopy->getDataSize();
		delete pCopy;
	}

	MFDataObject* pRetData=new MFDataObject();
	pRetData->setDataType(E_DataType::DATA_TYPE_N_BIT);
	pRetData->setDataByteSize(dataSize);
	pRetData->setData(serializedData);
	return pRetData;
}

uint32_t MFDataSerializer::getHeaderDataSize(){
	size_t dataSize=0;
	dataSize+=sizeof(uint32_t);//size of dataSize
	dataSize+=(sizeof(E_DataType));//Type of pData
	dataSize+=(sizeof(E_GuiElement));//Type of gui element
	return dataSize;
}

MFDataObject* MFDataSerializer::createSerializedData(
		MFStructurableDataSetup* pData,
		void* pOutData){
	//TODO test, its copy paste
	//|DataSize|SetupNameSize|SetupName|
	//DataCount|{Data1Header|Data1}=serialized MFDataObject|
	//Data2Header | Data2...
	std::vector<MFDataObject*> *pVecData=pData->getVecData();
	uint32_t dataSize=0;
	uint32_t dataCount=pVecData->size();
	dataSize+=sizeof(uint32_t);//serialized data size
	dataSize+=sizeof(uint32_t);//setup name length/size
	dataSize+=pData->getSetupName().size();//Setup name
	dataSize+=sizeof(uint32_t);//data counter
	dataSize+=(dataCount*getHeaderDataSize());//headers-size for sub data of pData
	dataSize+=pData->getStructureSize();//data data size
	void* serializedData=pOutData;
	if(serializedData==nullptr){
		serializedData=malloc(dataSize);
	}
	uint8_t* dstData=(uint8_t*)serializedData;

	/*data size*/
//	MFObject::printInfo("MFDataSerializer::createSerializedData(MFStr..DataSetup) - "
//			"serializing:\nsize: "+std::to_string(dataSize)+"\n"+
//			"setup name: "+pData->getSetupName()+"\n"+
//			"data count: "+std::to_string(dataCount));
	memcpy(dstData,&dataSize,sizeof(uint32_t));
	dstData+=sizeof(uint32_t);

	/*setup name*/
	uint32_t setupNameLength=pData->getSetupName().length();
	memcpy(dstData,&setupNameLength,sizeof(uint32_t));
	dstData+=sizeof(uint32_t);
	memcpy(dstData,pData->getSetupName().data(),setupNameLength);
	dstData+=pData->getSetupName().length();

	/*data count*/
	memcpy(dstData,&dataCount,sizeof(uint32_t));
	dstData+=sizeof(uint32_t);

	/*data*/
	MFDataObject* pCopy=nullptr;
	for(MFDataObject* pDO:*pVecData){
		pCopy=createSerializedData(pDO, dstData);
		dstData+=pCopy->getDataSize();
		delete pCopy;
	}

	MFDataObject* pRetData=new MFDataObject();
	pRetData->setDataType(E_DataType::DATA_TYPE_N_BIT);
	pRetData->setNBitSize(dataSize*8);
	pRetData->setDataByteSize(dataSize);
	pRetData->setData(serializedData);
	return pRetData;
}

bool MFDataSerializer::deserialize(
		void* in_data,
		MFDataObject* pOutData){
	uint8_t* src=(uint8_t*)in_data;
	uint32_t oaSize=*((uint32_t*)src);//over all size
	src+=sizeof(uint32_t);

	uint32_t dataSize=oaSize;
	dataSize-=sizeof(uint32_t);//minus size of oaSize
	dataSize-=sizeof(E_DataType);
	dataSize-=sizeof(E_GuiElement);
	if(dataSize==0){
		MFObject::printWarning("MFDataSerializer::deserialize - "
				"data size==0!");
	}

	E_DataType dataType=*((E_DataType*)src);
	src+=sizeof(E_DataType);
	pOutData->setDataType(dataType);

	E_GuiElement dataGuiElement=*((E_GuiElement*)src);
	src+=sizeof(E_GuiElement);
	pOutData->setGuiType(dataGuiElement);

	void* pDst=pOutData->getData();
	if(pDst==nullptr){
		MFObject::printWarning("MFDataSerializer::deserialize - "
				"pOutData->getData()==nullptr!");
		pOutData->setDataByteSize(dataSize);
	}else{
		if(pOutData->getDataSize()<dataSize){
			MFObject::printErr("MFDataSerializer::deserialize(void* in_data,MFDataObject& OutData) - "
					"failed, not enough memory for deserialization!");
			return false;
		}
	}
	if(!pOutData->writeData(src)){
		MFObject::printErr("MFDataSerializer::deserialize - failed to write to data"
				" object");
		return false;
	}
//	MFObject::printInfo("deserialize output data:\n"+pOutData->toString());
	return true;
}

bool MFDataSerializer::deserialize(
		void* in_data,
		MFStructurableData* pOutData){
	return false;
}

bool MFDataSerializer::deserialize(
		void* in_data,
		MFStructurableDataSetup* pOutData){
	//|DataSize|SetupNameSize|SetupName|
	//DataCount|{Data1Header|Data1}=serialized MFDataObject|
	//Data2Header | Data2...
	uint8_t* src=(uint8_t*)in_data;
	uint32_t dataSize=0;
	uint32_t stringLength=0;
	uint32_t dataCount=0;

	memcpy(&dataSize,src,sizeof(uint32_t));
	src+=sizeof(uint32_t);

	memcpy(&stringLength,src,sizeof(uint32_t));
	src+=sizeof(uint32_t);
	char* stringStart=(char*)(src);
	std::string setupName(stringStart,stringLength);
	src+=stringLength;

	memcpy(&dataCount,src,sizeof(uint32_t));
	src+=sizeof(uint32_t);

//	MFObject::printInfo("MFDataSerializer::deserialize - deserializing data "
//			"to MFStructurableDataSetup:\n"
//			"dataSize="+std::to_string(dataSize)+"\n"
//			"setupName="+setupName+"\n"
//			"dataCount="+std::to_string(dataCount));
	pOutData->setSetupName(setupName);

	/*check if count of input data matches with output data*/
	uint32_t outDataCount=pOutData->getVecData()->size();
	if(outDataCount!=dataCount){
		MFObject::printWarning("MFDataSerializer::deserialize - data count missmatch!"
				" Copying lowest possible count of data!\n"
				"output data count: "+std::to_string(outDataCount)+"\n"
				"input data count: "+std::to_string(dataCount));
		if(dataCount > outDataCount)
			dataCount=outDataCount;
	}

	/*deserialize input data to the data of output structure*/
	for(uint32_t i=0;i<dataCount;i++){
		MFDataObject *pDO=pOutData->getVecData()->at(i);
		if(!MFDataSerializer::deserialize(src, pDO)){
			MFObject::printWarning("MFDataSerializer::deserialize - deserialization "
					"of sub data failed!");
		}
		uint32_t size=*((uint32_t*)src);
		src+=size;
	}

	return true;
}


uint32_t MFDataSerializer::calculateDataSize(MFDataObject* pData){
	if(pData==nullptr){
		MFObject::printErr(" MFDataSerializer::calculateDataSize - pData==nullptr!");
		return 0;
	}
	size_t dataSize=0;
	dataSize+=sizeof(size_t);//size of dataSize
	dataSize+=(sizeof(E_DataType));//Type of pData
	dataSize+=(sizeof(E_GuiElement));//Type of gui element
	dataSize+=(sizeof(pData->getDataSize()));//size of data part
	return dataSize;
}

