/*
 * MFPrintTarget.h
 *
 *  Created on: 16.07.2019
 *      Author: michl
 */

#ifndef MFPRINTERS_MFPRINTTARGET_H_
#define MFPRINTERS_MFPRINTTARGET_H_
#include <mutex>
#include <iostream>
#include <vector>
#include "../MFObjects/MFObject.h"
#include "MFPrinterStructs.h"
class MFPrintTarget {
protected: /*virtual functions of MFPrintTarget*/
  /**
   * Virtual print method for data output. Make sure to use it on one thread or make it
   * threadsafe!
   * @param data
   * @param metaData - additional data for customized prints (Error red...)
   * @return
   */
  virtual bool printData(S_MFPrintMessage* pMsgData){
    printToConsol("MFPrintTarget::printData - not impl.! data for print:"+
        pMsgData->preFormattedMessage);
    return false;
  };

private:
  static std::mutex
  s_lockConsolPrint;

  std::mutex
  lockVecSubPrinters;

  std::vector<MFPrintTarget*>
  *mp_vecSubPrinters;

  uint32_t
  m_printIndex=0;

  bool
  m_isRegistered=false;

public:
  MFPrintTarget();
  MFPrintTarget(std::string filePath);
  virtual ~MFPrintTarget();

  bool print(S_MFPrintMessage* pMsgData);

  void addSubTarget(MFPrintTarget* pSubPrinter){
    lockVecSubPrinters.lock();
    mp_vecSubPrinters->push_back(pSubPrinter);
    lockVecSubPrinters.unlock();
  }

  /**
   * Statuc function for simple thread safe print.
   * @param data to print
   */
  static void printToConsol(std::string data);

  std::vector<MFPrintTarget*>* getVecSubPrinters(){return mp_vecSubPrinters;};

  /**
   * Registrates the printer to MFObject's static printers. After registration the
   * printer can be used with MFObject::print...("msg",printerIndex).
   */
  void registerPrinter();

  bool isRegistrated(){return m_isRegistered;}
  /**
   *
   * @return 0 if printer was not registrated. If registrated, this will return the
   * index into the MFObject's static vector of printers (used with MFObject::print...)
   */
  uint32_t getPrinterIndex(){return m_printIndex;}
};

#endif /* MFPRINTERS_MFPRINTTARGET_H_ */
