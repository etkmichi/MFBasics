/*
 * MFConsolePrinter.h
 *
 *  Created on: 30.07.2019
 *      Author: michl
 */

#ifndef MFREPORTS_MFCONSOLEPRINTER_H_
#define MFREPORTS_MFCONSOLEPRINTER_H_

#include "MFPrintTarget.h"
#include "MFPrinterStructs.h"

class MFConsolePrinter: public MFPrintTarget {
protected: /*virtual functions of MFPrintTarget*/
  /**
   * Virtual print method for data output. Make sure to use it on one thread or make it
   * threadsafe!
   * @param data
   * @param metaData - additional data for customized prints (Error red...)
   * @return
   */
  virtual bool printData(S_MFPrintMessage* pMsgData);
public:
	MFConsolePrinter();
	virtual ~MFConsolePrinter();

};

#endif /* MFREPORTS_MFCONSOLEPRINTER_H_ */
