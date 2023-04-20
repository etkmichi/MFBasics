/*
 * MFDataSerializer.h
 *
 *  Created on: 27.04.2020
 *      Author: michl
 */

#ifndef MFDATA_MFDATASERIALIZER_H_
#define MFDATA_MFDATASERIALIZER_H_
#include "MFDataObject.h"
#include "MFStructurableData.h"
#include "MFStructurableDataSetup.h"
/**
 * This class provides functionalities to serialize data.
 * The data can be of given structures of MFBasics data classes:
 * MFDataObject, MFStructurableData, MFStructurableDataBuffer
 */
class MFDataSerializer {
public:
	/**
	 * serializes pData to (OA DataSize | DataType | GuiElement | Data)
	 * @param pData - the data object which shall be serialized.
	 * @param pOutData - if not nullptr, then it will be used to store the serialized
	 * data. The returned MFDataObject's data pointer will be pOutData.
	 * @return a data object which contains the serialized data.
	 * The returned object must be deleted if it's not needed anymore.
	 * Deletion/manipulation of the pData or freeing the sub data, will not
 	 * affect the returned serialized data.
 	 * During serialization data may not be changed, synchronization must be done
 	 * externally!
	 */
	static MFDataObject* createSerializedData(
			MFDataObject* pData,
			void* pOutData=nullptr);

	static MFDataObject* createSerializedData(
			MFStructurableData* pData,
			void* pOutData=nullptr);
	//TODO calculateSize functions for serialized buffer
	//	-> needed for external buffer creation f.e. if more than one setup needs
	//		to be serialized into one buffer
	//Maybe create serialization function with vector<MFS...> pData
	static MFDataObject* createSerializedData(
			MFStructurableDataSetup* pData,
			void* pOutData=nullptr);

	static uint32_t calculateDataSize(MFDataObject* pData);

	static uint32_t getHeaderDataSize();

	static bool deserialize(
			void* in_data,
			MFDataObject* pOutData);

	static bool deserialize(
			void* in_data,
			MFStructurableData* pOutData);

	static bool deserialize(
			void* in_data,
			MFStructurableDataSetup* pOutData);

};

#endif /* MFDATA_MFDATASERIALIZER_H_ */
