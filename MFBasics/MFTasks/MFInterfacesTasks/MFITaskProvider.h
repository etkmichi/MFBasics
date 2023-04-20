/*
 * MFITaskProvider.h
 *
 *  Created on: 14.05.2020
 *      Author: michl
 */

#ifndef MFTASKS_MFINTERFACESTASKS_MFITASKPROVIDER_H_
#define MFTASKS_MFINTERFACESTASKS_MFITASKPROVIDER_H_
#include "../MFAbstractDataProcessingTask.h"
#include "../../MFData/MFStructurableDataBuffer.h"
#include "../../MFThreadSystem/MFTaskThread.h"
class MFITaskProvider {
protected:
	MFTaskThread
		*mp_defaultDispatchThread=nullptr;
public://TODO add string taskName to add functions
	virtual ~MFITaskProvider(){};

	virtual uint32_t addTask(MFAbstractTask* pTask){
		MFObject::printErr("MFITaskProvider::addTask 1 - no impl.!");
		return 0xFFFFFFFF;
	}

	/**
	 * Adds the task to the task provider (f.e. MFTaskManager) and returns the task's index
	 * @param pTask
	 * @param pTaskDataProvider
	 * @return
	 */
	virtual uint32_t addTask(
			MFAbstractDataProcessingTask* pTask,
			MFStructurableDataBuffer* pTaskDataProvider){
		MFObject::printErr("MFITaskProvider::addTask 2 - no impl.!");
		return 0xFFFFFFFF;
	}

	void setDefaultDispatchThread(MFTaskThread* pThread){mp_defaultDispatchThread=pThread;}
};

#endif /* MFTASKS_MFINTERFACESTASKS_MFITASKPROVIDER_H_ */
