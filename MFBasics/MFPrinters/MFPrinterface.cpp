/*
 * MFPrinterface.cpp
 *
 *  Created on: 16.07.2019
 *      Author: michl
 */

#include "../MFPrinters/MFPrinterface.h"

#include "../MFTime/MFTimeStructs.h"
#include "../MFTime/MFTimeHelper.h"
int MFPrinterface::ms_msgCounter=0;
std::mutex MFPrinterface::lockStaticRes=std::mutex();
MFPrinterface::MFPrinterface():
	MFTaskThread("MFPrinterface",false),
	lockVecMessages(),
	lockVecPrintTargets(),
	lockPrintLoop()
{
	m_tag=-1;
	m_tagName="";
	mp_defaultPrinter = new MFConsolePrinter();
	mp_printTask=new MFPrintTask(this);
	//m_vecMessages={};
	mp_nextMsg=nullptr;
	mp_lastMsg=nullptr;
	mp_vecPrintTargets=new std::vector<MFPrintTarget*>();
	mp_vecPrintTargets->push_back(mp_defaultPrinter);
	std::cout<<"MFPrinterface::MFPrinterface - Initialization of print output."<<std::endl;
	addTask(mp_printTask);
	MFObject::pPrinter=this;
	startDetached();//TODO static init withi MFObject -> what if run() call from
	//created thread is executed before the pointer of the static var is assigned?
}

MFPrinterface::~MFPrinterface() {
	mp_vecPrintTargets->clear();

	for(S_MFPrintMessage* pMsg=mp_nextMsg;pMsg!=nullptr;){
		S_MFPrintMessage* last=pMsg;
		pMsg=pMsg->nextMsg;
		delete last;
	}
	delete mp_defaultPrinter;
	delete mp_printTask;
}

//void MFPrinterface::setPrintTarget(MFPrintTarget *output){
//	lockVecPrintTargets.lock();
//	mp_vecPrintTargets->clear();
//	if(output!=nullptr){
//		mp_vecPrintTargets->push_back(output);
//	}
//	lockVecPrintTargets.unlock();
//}
uint32_t MFPrinterface::addPrintTarget(MFPrintTarget* output){
	lockVecPrintTargets.lock();
	if(output!=nullptr){
		mp_vecPrintTargets->push_back(output);
	}else{
	  mp_defaultPrinter->printToConsol(std::string("error MFPrinterface::addPrintTarget -"
	      " MFPrintTarget* output==nullptr! adding default printer!"));
	  mp_vecPrintTargets->push_back(mp_defaultPrinter);
	}
	uint32_t index=mp_vecPrintTargets->size()-1;
	lockVecPrintTargets.unlock();
	return index;
}

void MFPrinterface::printErr(std::string err, const uint32_t &printerIndex){
	/*The message will be deleted in the print loop*/
	int val=0;
	lockStaticRes.lock();
	val=ms_msgCounter;
	ms_msgCounter++;
	lockStaticRes.unlock();
	S_MFPrintMessage* pMsg=createMessageMetaData(err, "error "+std::to_string(val));
	lockVecPrintTargets.lock();
	pMsg->originalMessage=err;
	if(printerIndex >= mp_vecPrintTargets->size()){
    pMsg->pPrinter=mp_vecPrintTargets->at(0);
    pMsg->printerIndex=0;
	}else{
    pMsg->pPrinter=mp_vecPrintTargets->at(printerIndex);
    pMsg->printerIndex=printerIndex;
	}
  lockVecPrintTargets.unlock();
  pMsg->messageType=E_MSG_TYPE_ERROR;
	lockVecMessages.lock();
	if(mp_nextMsg==nullptr){
		mp_nextMsg=pMsg;
		mp_lastMsg=pMsg;
		lockPrintLoop.unlock();/*print loop go -> dont forget to lock it if no next msg*/
	}else{
		mp_lastMsg->nextMsg=pMsg;
		mp_lastMsg=pMsg;
	}
	lockVecMessages.unlock();
}

void MFPrinterface::printWarning(std::string warning, const uint32_t &printerIndex){
	int val=0;
	lockStaticRes.lock();
	val=ms_msgCounter;
	ms_msgCounter++;
	lockStaticRes.unlock();
	S_MFPrintMessage* pMsg=createMessageMetaData(warning,"warning "+std::to_string(val));
  lockVecPrintTargets.lock();
  if(printerIndex >= mp_vecPrintTargets->size()){
    pMsg->pPrinter=mp_vecPrintTargets->at(0);
    pMsg->printerIndex=0;
  }else{
    pMsg->pPrinter=mp_vecPrintTargets->at(printerIndex);
    pMsg->printerIndex=printerIndex;
  }
  pMsg->messageType=E_MSG_TYPE_WARNING;
  lockVecPrintTargets.unlock();
	lockVecMessages.lock();
	if(mp_nextMsg==nullptr){
		mp_nextMsg=pMsg;
		mp_lastMsg=pMsg;
		lockPrintLoop.unlock();/*print loop go -> dont forget to lock it if no next msg*/
	}else{
		mp_lastMsg->nextMsg=pMsg;
		mp_lastMsg=pMsg;
	}
	lockVecMessages.unlock();
}

void MFPrinterface::printInfo(std::string info, const uint32_t &printerIndex){
	/*The message will be deleted in the print loop*/
	int val=0;
	lockStaticRes.lock();
	val=ms_msgCounter;
	ms_msgCounter++;
	lockStaticRes.unlock();
	S_MFPrintMessage* pMsg=createMessageMetaData(info,"info "+std::to_string(val));
  lockVecPrintTargets.lock();
  if(printerIndex >= mp_vecPrintTargets->size()){
    pMsg->pPrinter=mp_defaultPrinter;
    pMsg->printerIndex=0;
  }else{
    pMsg->pPrinter=mp_vecPrintTargets->at(printerIndex);
    pMsg->printerIndex=printerIndex;
  }
  lockVecPrintTargets.unlock();
  pMsg->messageType=E_MSG_TYPE_INFO;
	lockVecMessages.lock();
  if(mp_nextMsg==nullptr){
    mp_nextMsg=pMsg;
    mp_lastMsg=pMsg;
    lockPrintLoop.unlock();/*print loop go -> dont forget to lock it if no next msg*/
  }else{
    mp_lastMsg->nextMsg=pMsg;
    mp_lastMsg=pMsg;
  }
  lockVecMessages.unlock();
}

S_MFPrintMessage* MFPrinterface::createMessageMetaData(
    std::string &data,
    std::string msgType){
	/*The message will be deleted in the print loop*/
	S_MFPrintMessage* msg=new S_MFPrintMessage();
	if(m_tag>-1){
		msg->tagName=m_tagName;
		msg->tagUID=m_tag;
	}

	//TODO print milliseconds
	msg->msgTimestamp = U_Clock::now();
	msg->type=msgType;
	msg->preFormattedMessage=data;
	return msg;
}

void MFPrinterface::createMessage(S_MFPrintMessage* pMsg){
	std::string outData = pMsg->type ;
	   // " (tagName: "+pMsg->tagName+"; tagID: "+std::to_string(pMsg->tagUID);
	outData+=" (time: ";
	pMsg->timeAsString=MFTimeHelper::toString(pMsg->msgTimestamp, true);
	outData+=MFTimeHelper::toString(pMsg->msgTimestamp, true);
//  struct timespec ts;
//  clock_getres(CLOCK_MONOTONIC, &ts);

	outData+=") "+(pMsg->preFormattedMessage) +"\n";
	pMsg->preFormattedMessage=outData;
}

void MFPrinterface::printNext(){
  lockPrintLoop.lock();
  lockVecMessages.lock();
	S_MFPrintMessage* nextMessage=mp_nextMsg;
  lockVecMessages.unlock();
  while(nextMessage==nullptr){
    lockPrintLoop.lock();
    lockVecMessages.lock();
    nextMessage=mp_nextMsg;
    lockVecMessages.unlock();
  }
	lockVecMessages.lock();

  mp_nextMsg=mp_nextMsg->nextMsg;
  if(mp_nextMsg!=nullptr){/*Another msg should be available for the next run*/
    lockPrintLoop.unlock();/*unlock for next run*/
  }

	createMessage(nextMessage);
  lockVecMessages.unlock();

	//TODO dispatch counter and difference to static msg counter.
	//if too many msgs are not dispatchd stop creating new!

	/*Iterate through the printers to print the data.*/
	lockVecPrintTargets.lock();
	MFPrintTarget* pPrinter=mp_vecPrintTargets->at(nextMessage->printerIndex);
  lockVecPrintTargets.unlock();
  if(pPrinter==nullptr){
    MFPrintTarget::printToConsol("MFPrinterface::printNext - "
        "couldn't print to print target (==nullptr)! Msg:\n"+nextMessage->preFormattedMessage);
  }else if(!pPrinter->print(nextMessage)){
    MFPrintTarget::printToConsol("MFPrinterface::printNext - "
        "failed printing to print target! Msg:\n"+nextMessage->preFormattedMessage);
  }
	delete(nextMessage);
	addTask(mp_printTask);
}


