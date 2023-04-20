/*
 * MFAbstractDataProcessingTask.h
 *
 *  Created on: 19.03.2020
 *      Author: michl
 */

#ifndef MFTASKS_MFABSTRACTDATAPROCESSINGTASK_H_
#define MFTASKS_MFABSTRACTDATAPROCESSINGTASK_H_
#include <vector>
#include <mutex>

#include "../MFData/MFInterfacesData/MFIBufferSink.h"
#include "MFAbstractTask.h"
#include "../MFData/MFStructurableData.h"
#include "../MFData/MFInterfacesData/MFIStructurableDataCreator.h"
#include "../MFThreadSystem/MFIWakableThread.h"

/**
 * This task provides functionality for processing data. This task will process
 * all data which was added before doWork call. The input data queue
 * will be multiplexed, to ensure that data can be added while previously added data is processing.
 */
class MFAbstractDataProcessingTask :
		public MFAbstractTask,
		public MFIStructurableDataCreator {
private:
	std::vector<MFStructurableData*>
		*mp_vecInputData,
		*mp_vecProcessingData;
	std::mutex
		lockVecInput,
		lockVecProcessingData;
	MFStructurableData
		*mp_dummyData;
	MFIBufferSink
		*mp_bufferSink;
	MFIStructurableDataCreator
		*mp_externalDataCreator;
	bool
		m_enableReprocessing=false;

protected:
	MFIWakableThread
		*mp_wakableThread;

public:/*virtual functions of MFAbstractDataProcessingTask*/

  /**
   * The prepareInputData is used for pre data processing tasks.
   * This function will be called during addInputData(...).
   * @param pInputData - input data which shall be prepared (f.e. decoded).
   */
  virtual void prepareInputData(MFStructurableData* pInputData){};

  virtual void postProcessing(){};

  /**
   * Task specific processing of pData. pData must be in a task compatible format.
   * Called during doWork() funtion with the added input data
   * (addInputData(...)) as parameter.
   * @param pData - data which shall be processed in a task specific way. Must
   * be a task compatible structure!
   * @return true if processing was successfull.
   */
  virtual bool processData(MFStructurableData* pData){
    MFObject::printWarning("MFAbstractDataProcessingTask::processData - no"
        "implementation!");
    return true;
  };

  virtual bool undoWork(){return false;};
public: /*virtual functions of MFIStructurableDataCreator*/
  virtual MFStructurableData* createNewEmptyData(){
    if(mp_externalDataCreator!=nullptr){
      return mp_externalDataCreator->createNewEmptyData();
    }
    MFObject::printErr("virtual MFAbstractDataProcessingTask::"
        "createNewEmptyData() - dummy data will be returned!");
    return mp_dummyData;
  };

public:
	MFAbstractDataProcessingTask();
	virtual ~MFAbstractDataProcessingTask();

	/**
	 * Adds data for processing. This function is thread safe!
	 * @param pInputData
	 * @param prepareInput - if true, prepareInputData function of subclass will be
	 * called with the given pInputData as parameter. The prepareInputData is used
	 * for pre data processing tasks.
	 */
	void addInputData(
			MFStructurableData* pInputData,
			bool prepareInput=true);

	uint32_t getInputDataCount(){
		uint32_t ret=0;
		lockVecInput.lock();
		ret=mp_vecInputData->size();
		lockVecInput.unlock();
		return ret;
	}

	/**
	 * This function can be used to set an external data creator. The default
	 * implementation of createNewEmptyData() will use the set data creator.
	 * @param pDataCreator
	 */
	void setExternalDataCreator(MFIStructurableDataCreator* pDataCreator){
		mp_externalDataCreator=pDataCreator;
	}


	bool doWork();

	/**
	 * If a return buffer is set, all added data will be returned to the given buffer after
	 * processing.
	 * @param pBuffer
	 */
	void setBufferSink(MFIBufferSink* pBuffer){mp_bufferSink=pBuffer;}

	/**
	 * If set, addInputData will wake up the given MFIWakableThread.
	 * @param pWakableThread
	 */
	void setWakeableThread(MFIWakableThread *pWakableThread){mp_wakableThread=pWakableThread;};

	/**
	 * If reprocessing on failure is enabled, data will be added again if processing failed.
	 * If not enabled
	 * @def disabled by default
	 * @param enable
	 */
	void enableReprocessingOnFailure(bool enable){m_enableReprocessing=enable;};
	const uint32_t& getTaskManagerID(){return m_taskManagerID;};
	const uint32_t& getTaskManagerIndex(){return m_taskIndex;};
};

#endif /* MFTASKS_MFABSTRACTDATAPROCESSINGTASK_H_ */
