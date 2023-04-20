/*
 * MFPrintTask.h
 *
 *  Created on: 31.07.2019
 *      Author: michl
 */

#ifndef MFPRINTERS_MFPRINTTASK_H_
#define MFPRINTERS_MFPRINTTASK_H_

class MFPrintTask;

#include <iostream>
#include "../MFPrinters/MFPrinterface.h"
#include "../MFTasks/MFAbstractTask.h"

class MFPrintTask : public MFAbstractTask {
private:
	MFPrinterface* p_printInterface;
public:
	MFPrintTask(MFPrinterface* printInterface);
	virtual ~MFPrintTask();
	bool doWork();
	bool undoWork();
};

#endif /* MFPRINTERS_MFPRINTTASK_H_ */
