/*
 * MFConsolePrinter.cpp
 *
 *  Created on: 30.07.2019
 *      Author: michl
 */

#include "MFConsolePrinter.h"

MFConsolePrinter::MFConsolePrinter() {
	// TODO Auto-generated constructor stub

}

MFConsolePrinter::~MFConsolePrinter() {
	// TODO Auto-generated destructor stub
}

bool MFConsolePrinter::printData(S_MFPrintMessage* pMsgData){
	MFPrintTarget::printToConsol(pMsgData->preFormattedMessage);
	return true;
}
