/*
 * MFCallbackTask.cpp
 *
 *  Created on: 23.03.2021
 *      Author: michl
 */

#include "MFCallbackTask.h"
#include "../MFBasicDefines.h"

MFCallbackTask::MFCallbackTask() {
  // TODO Auto-generated constructor stub

}

MFCallbackTask::~MFCallbackTask() {
  // TODO Auto-generated destructor stub
}

bool MFCallbackTask::doWork(){
  bool ret=true;
  lockVecCallbacks.lock();
  MFICallback* pC=nullptr;
  for(uint32_t i=0; i<vecCallbacks.size();i++){
    pC=vecCallbacks.at(i);
    if(pC==nullptr){
      continue;
    }
    lockVecCallbacks.unlock();
    if(!pC->callback()){
      P_WRN("failed execution of callback!");
      ret=false;
    }
    lockVecCallbacks.lock();
    continue;
  }
  vecCallbacks.clear();
  lockVecCallbacks.unlock();
  return ret;
}

int MFCallbackTask::addCallback(MFICallback* pCallback){
  /*During execution another callback can be added*/
  lockVecCallbacks.lock();
  int callbackIndex=vecCallbacks.size();
  vecCallbacks.push_back(pCallback);
  lockVecCallbacks.unlock();
  return callbackIndex;
}
