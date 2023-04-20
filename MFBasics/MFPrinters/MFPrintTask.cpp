/*
 * MFPrintTask.cpp
 *
 *  Created on: 31.07.2019
 *      Author: michl
 */

#include "MFPrintTask.h"

MFPrintTask::MFPrintTask(MFPrinterface* printInterface) {
	p_printInterface=printInterface;
}

MFPrintTask::~MFPrintTask() {
}

bool MFPrintTask::doWork(){
	if(p_printInterface!=nullptr){
		p_printInterface->printNext();
	}else{
		std::cout<<"-- Sth. went wrong in the print task! p_printInterface==nullptr! --\n";
		return false;
	}
	return true;
}

bool MFPrintTask::undoWork(){
	return false;
}
