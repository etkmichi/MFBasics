/*
 * MFDataDeletion.h
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#ifndef MFDATADELETERCLASSES_MFDATADELETION_H_
#define MFDATADELETERCLASSES_MFDATADELETION_H_
#include "../MFTime/MFTickCounter.h"
#include "../MFData/MFStructurableDataBuffer.h"
#include "MFDeletionTask.h"
#include "MFDataDeleterThread.h"
#include <vector>
#include <mutex>
class MFDataDeletion {
private:
	static std::mutex
		sm_lockBuffer;
	static MFStructurableDataBuffer
		*smp_bufferProvider;
	static MFDeletionTask
		*smp_dataDeletionTask;
	static MFDataDeleterThread
		*smp_deletionThread;
public:
	static uint32_t
		sm_maxDeletableObjects;//2kBytes preallocated buffer
	MFDataDeletion();
	virtual ~MFDataDeletion();
	static void initStaticDataDeletion();
	static bool addData(void* data,int64_t deletionDelayInMillis);
};

#endif /* MFDATADELETERCLASSES_MFDATADELETION_H_ */
