/*
 * MFDeletionTask.h
 *
 *  Created on: 02.04.2020
 *      Author: michl
 */

#ifndef MFDATADELETERCLASSES_MFDELETIONTASK_H_
#define MFDATADELETERCLASSES_MFDELETIONTASK_H_
#include <thread>
#include "../MFTasks/MFAbstractDataProcessingTask.h"
class MFDeletionTask: public MFAbstractDataProcessingTask {
private:
	int64_t
		m_nextDeletionTime;
public:
	MFDeletionTask();
	virtual ~MFDeletionTask();
	void prepareInputData(MFStructurableData* pData);
	bool processData(MFStructurableData* pData);

	/**
	 *
	 * @return time point of next deletion. Before first iteration
	 * iteration it will return 0.
	 */
	int64_t getNextDeletionTimepoint(){
		return m_nextDeletionTime;
	};
};

#endif /* MFDATADELETERCLASSES_MFDELETIONTASK_H_ */
