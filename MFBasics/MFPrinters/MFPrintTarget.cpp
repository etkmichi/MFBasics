/*
 * MFPrintTarget.cpp
 *
 *  Created on: 16.07.2019
 *      Author: michl
 */

#include "../MFPrinters/MFPrintTarget.h"
#include "../MFPrinters/MFPrinterface.h"

std::mutex MFPrintTarget::s_lockConsolPrint;
MFPrintTarget::MFPrintTarget() {
  mp_vecSubPrinters=new std::vector<MFPrintTarget*>();
}

MFPrintTarget::~MFPrintTarget() {
	// TODO Auto-generated destructor stub
}

void MFPrintTarget::printToConsol(std::string data){
	s_lockConsolPrint.lock();
	std::cout<<data<<std::endl;
	s_lockConsolPrint.unlock();
}

void MFPrintTarget::registerPrinter(){
  MFPrinterface* pPrinter=static_cast<MFPrinterface*>(MFObject::pPrinter);
  m_printIndex=pPrinter->addPrintTarget(this);
}

bool MFPrintTarget::print(S_MFPrintMessage* pMsgData){
  bool ret=true;
  ret&=printData(pMsgData);
  if(!ret){
    printToConsol("MFPrintTarget::print - default print failed!");
    ret=true;
  }
  lockVecSubPrinters.lock();
  uint32_t counter=0;
  for(MFPrintTarget* pT:*mp_vecSubPrinters){
    counter++;
    if(pT)ret=pT->print(pMsgData);
    if(!ret){
        printToConsol("MFPrintTarget::print - sub print failed! index:"
            " "+std::to_string(counter));
    }
  }
  lockVecSubPrinters.unlock();
  return ret;
}
