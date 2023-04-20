/*
 * MFPrinterStructs.h
 *
 *  Created on: 26.08.2020
 *      Author: michl
 */

#ifndef MFPRINTERS_MFPRINTERSTRUCTS_H_
#define MFPRINTERS_MFPRINTERSTRUCTS_H_
#include <cstring>
#include "../MFTime/MFTimeStructs.h"
enum E_MESSAGE_TYPE {
  E_MSG_TYPE_ERROR,
  E_MSG_TYPE_WARNING,
  E_MSG_TYPE_INFO,
  E_MSG_TYPE_UNKNOWN
};
struct S_MFPrintMessage{
  int tagUID=-1;
  U_TimePoint msgTimestamp;
  E_MESSAGE_TYPE messageType=E_MSG_TYPE_UNKNOWN;
  std::string type="";
  std::string tagName="-Not Set!-";
  std::string originalMessage="";
  std::string preFormattedMessage="";
  std::string timeAsString="";
  uint32_t printerIndex=0;
  void* pPrinter=nullptr;/*type: MFPrintTarget!*/
  S_MFPrintMessage* nextMsg=nullptr;
  void* userData=nullptr;
};



#endif /* MFPRINTERS_MFPRINTERSTRUCTS_H_ */
