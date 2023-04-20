/*
 * MFCallbackTask.h
 *
 *  Created on: 23.03.2021
 *      Author: michl
 */

#ifndef MFTASKS_MFCALLBACKTASK_H_
#define MFTASKS_MFCALLBACKTASK_H_

#include <vector>
#include "MFAbstractTask.h"
#include "../MFCallback/MFICallback.h"

class MFCallbackTask: public MFAbstractTask {
private:
  std::mutex
  lockVecCallbacks;
  std::vector<MFICallback*>
  vecCallbacks;

public:/*virtual functions of MFAbstractTask*/
  virtual bool doWork();

  virtual bool undoWork(){return true;};
public:
  MFCallbackTask();
  virtual ~MFCallbackTask();

  /**
   *
   * @param pCallback to add for execution
   * @return callback index
   */
  int addCallback(MFICallback* pCallback );
};

#endif /* MFTASKS_MFCALLBACKTASK_H_ */
