/*
 * MFStructurableDataBuffer.h
 *
 *  Created on: 20.03.2020
 *      Author: michl
 */

#ifndef MFDATA_MFSTRUCTURABLEDATABUFFER_H_
#define MFDATA_MFSTRUCTURABLEDATABUFFER_H_
#include <vector>
#include <mutex>
#include "MFDataObjectBuffer.h"
#include "MFInterfacesData/MFIBufferSink.h"
#include "MFInterfacesData/MFIBufferSource.h"
#include "MFStructurableData.h"
#include "MFInterfacesData/MFIStructurableDataCreator.h"
/**
 * This class represents a buffer of MFStructurableData. With the take function, buffers
 * can be taken.
 * The buffers which were taken, must be returned with the return function!
 * Take care to call the init function
 * before using an object of this class!
 */
class MFStructurableDataBuffer :
		public MFIStructurableDataCreator,
		public MFIBufferSink,
		public MFIBufferSource {
private:
	MFStructurableData
		*mp_baseStructure,
		*mp_dummyBuffer;
	bool
		m_isInitialized=false;
	MFDataObjectBuffer
		*mp_sharedDataBuffer;
	std::vector<MFStructurableData*>
		*mp_vecAvailableBuffers,
		*mp_vecCreatedBuffers;
	MFIStructurableDataCreator
		*mp_dataCreator;
	std::mutex
		lockBufferMemory,
		lockVecAvailableBuffers,
		lockVecStatistics;
	int32_t
		m_currentIndex=0;
	uint32_t
		m_objectCount=0;
	std::vector<uint32_t>
		m_vecStatisticsCurrentIndex;/*data for buffer statistics*/
	uint64_t
		m_bufferSize=0;
	std::string
		m_bufferName="MFStructurableDataBuffer";

public:
	/**
	 *
	 * @param pDataCreator - data creator used to create the buffers during init.
	 * @param objectCount - count of buffers
	 */
	MFStructurableDataBuffer(
			MFIStructurableDataCreator* pDataCreator,
			uint32_t objectCount);
	/**
	 * This constructor uses a copy of pBaseStructure for data creation.
	 * @param pBaseStructure - The structure will be copied and used as buffer creation mask.
	 * The pBaseStructure will be copied, if not needed, it can be deleted after this constructor call.
	 * @param objectCount - count of buffers
	 */
	MFStructurableDataBuffer(
			MFStructurableData* pBaseStructure,
			uint32_t objectCount);

	MFStructurableData* createNewEmptyData();

	virtual ~MFStructurableDataBuffer();

	/**
	 * Inits all buffers and the related data.
	 * @return
	 */
	bool initBuffer();

	/**
	 * Takes a buffer from the initialized data. The taken buffer must be returned, to
	 * ensure that MFIBufferSource doesn't run out of buffers.
   * This function should be thread safe.
	 * @return nullptr if no buffer available or a buffer which must be returned by
	 * returnData(...).
	 */
	MFStructurableData* takeData();

	/**
	 * Do not return data which was not taken from this buffer (by takeData())!!!
	 * Do not return same data twice!
	 * This function should be thread safe.
	 * @param pData
	 */
	bool returnData(MFStructurableData* pData);

	uint32_t getAvailableBufferCount();
	uint32_t getMaxBufferCount();

	void setBufferName(std::string name){m_bufferName=name;}
	std::string getBufferName(){return m_bufferName;}

	void fillAll(uint32_t fill);
};

#endif /* MFDATA_MFSTRUCTURABLEDATABUFFER_H_ */
