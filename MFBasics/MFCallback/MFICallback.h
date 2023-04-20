/*
 * MFIFunctionCallback.h
 *
 *  Created on: 17.08.2020
 *      Author: michl
 */

#ifndef MFIFUNCTIONCALLBACK_H_
#define MFIFUNCTIONCALLBACK_H_
#include "../MFBasicDefines.h"
/**
 * This interface can be implemented to provide a function callback
 * from the gui. If more than one callback shall be implemented within
 * a class, implement the virtual bool guiCallback(uint32_t switchVal)
 * function.
 */
class MFICallback {
private:
  uint32_t switchVal=0;
  void* pUserData=nullptr;
public: /*virtual functions of MFIFunctionCallback*/
  /**
   * @deprecated !!!
   * @param switchVal
   * @param userData
   * @return
   */
  virtual bool functionCallback(uint32_t switchVal=0,void* userData=nullptr){
    return false;
  }
  virtual bool callback(uint32_t switchVal,void* userData=nullptr){
    if(userData!=nullptr)
    MFObject::printErr("MFIFunctionCallback::guiCallback - no impl.! switchVal:"
        +std::to_string(switchVal)
       +"\nuserData="+std::to_string(*(static_cast<uint64_t*>(userData))));
    else
      MFObject::printErr("MFIFunctionCallback::guiCallback - no impl.! switchVal:"
          +std::to_string(switchVal));
    return false;
  }
  virtual void errorCallback(uint32_t switchVal,const std::string &error){
    MFObject::printErr("MFIFunctionCallback::errorCallback - "
        "switchVal: " +std::to_string(switchVal)+
        "/nerrorMsg:"+error);
    return;
  }
public:
  MFICallback(){
  }
  virtual ~MFICallback(){
  }
  bool callback(){
    return callback(switchVal, pUserData);
  }

  void* getPUserData() const {
    return pUserData;
  }

  void setPUserData(void *pUserData = nullptr) {
    this->pUserData = pUserData;
  }

  uint32_t getSwitchVal() const {
    return switchVal;
  }

  void setSwitchVal(uint32_t switchVal = 0) {
    this->switchVal = switchVal;
  }
};

#endif /* MFIFUNCTIONCALLBACK_H_ */
