/*
 * MFPrinterface.h
 *
 *  Created on: 16.07.2019
 *      Author: michl
 */

#ifndef MFPRINTERS_MFPRINTERFACE_H_
#define MFPRINTERS_MFPRINTERFACE_H_

class MFPrinterface;


#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "../MFThreadSystem/MFTaskThread.h"
#include "../MFPrinters/MFPrintTarget.h"
#include "../MFPrinters/MFConsolePrinter.h"
#include "../MFPrinters/MFPrintTask.h"

/**
 * This class provides printing functionality.
 * It can act thread independend and offers queues for printing messages.
 */
class MFPrinterface : MFTaskThread {

private:
	int
		m_tag;
	static int
		ms_msgCounter;
	std::string
		m_tagName;

	MFPrintTarget*
		mp_defaultPrinter;

	S_MFPrintMessage
		*mp_nextMsg,
		*mp_lastMsg;
	std::vector<MFPrintTarget*>
	*mp_vecPrintTargets;

	std::mutex
		lockVecMessages,
		lockVecPrintTargets,
		lockPrintLoop;
	static std::mutex
		lockStaticRes;

	MFPrintTask*
		mp_printTask;


public:

	MFPrinterface();
	virtual ~MFPrinterface();
	int getUniqueTagID();
	void printNext();
	void setTag(int tagUID,std::string tagName);

	/**
	 * Sets a single print target connected to the tagUID. Removes all added print targets.
	 * @param tagUID
	 * @param output
	 */
//	void setPrintTarget(MFPrintTarget *output);

	/**
	 * Adds a print target for multiple prints.
	 * @param tagUID
	 * @param output
	 */
	uint32_t addPrintTarget(MFPrintTarget *output);

	/**
	 * Print error message to the system output
	 * @param err
	 */
	void printErr(std::string err,const uint32_t &printerIndex=0);

	/**
	 * Print error message to the output.
	 * @param err
	 */
	void printWarning(std::string warning,const uint32_t &printerIndex=0);
	void printInfo(std::string info,const uint32_t &printerIndex=0);

	S_MFPrintMessage* createMessageMetaData(std::string &data,std::string msgType);
	void createMessage(S_MFPrintMessage* pMsg);
};

#endif /* MFPRINTERS_MFPRINTERFACE_H_ */
