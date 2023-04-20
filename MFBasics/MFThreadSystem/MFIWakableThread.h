/*
 * MFIWakableThread.h
 *
 *  Created on: 03.04.2020
 *      Author: michl
 */

#ifndef MFTHREADSYSTEM_MFIWAKABLETHREAD_H_
#define MFTHREADSYSTEM_MFIWAKABLETHREAD_H_

class MFIWakableThread {
public:
	virtual ~MFIWakableThread(){};
	virtual void wakeUp(){};
};

#endif /* MFTHREADSYSTEM_MFIWAKABLETHREAD_H_ */
