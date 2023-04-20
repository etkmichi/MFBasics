/*
 * MFDataDeleterThread.h
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#ifndef MFDATADELETERCLASSES_MFDATADELETERTHREAD_H_
#define MFDATADELETERCLASSES_MFDATADELETERTHREAD_H_
#include "../MFThreadSystem/MFTaskThread.h"
#include "MFDeletionTask.h"
class MFDataDeleterThread: public MFTaskThread {
private:
	MFDeletionTask
		*mp_deletionTask;
public:
	MFDataDeleterThread();
	virtual ~MFDataDeleterThread();
	void postExecution();
	void setDeletionTask(MFDeletionTask* pTask){mp_deletionTask=pTask;};

};

#endif /* MFDATADELETERCLASSES_MFDATADELETERTHREAD_H_ */
