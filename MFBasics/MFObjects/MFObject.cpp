/*
 * MFObject.cpp
 *
 *  Created on: 09.07.2019
 *      Author: michl
 */

#include "MFObject.h"

#include "../MFPrinters/MFPrinterface.h"
void* MFObject::pPrinter=((void*)new MFPrinterface());


MFObject::MFObject() {
	// TODO Auto-generated constructor stub
}

MFObject::~MFObject() {
	// TODO Auto-generated destructor stub
}

void MFObject::printErr(const std::string& txt,const uint32_t &printerIndex){
  ((MFPrinterface*)pPrinter)->printErr(txt,printerIndex);
}

void MFObject::printWarning(const std::string& txt,const uint32_t &printerIndex){
  ((MFPrinterface*)pPrinter)->printWarning(txt,printerIndex);
}

void MFObject::printInfo(const std::string& txt,const uint32_t &printerIndex){
  ((MFPrinterface*)pPrinter)->printInfo(txt,printerIndex);
}

void MFObject::printVec3(const glm::vec3& vector,const uint32_t &printerIndex){
  ((MFPrinterface*)pPrinter)->printInfo("x="+std::to_string(vector.x)+
			" y="+std::to_string(vector.y)+
			" z="+std::to_string(vector.z),printerIndex);
}

void MFObject::printVec4(const glm::vec4& vector,const uint32_t &printerIndex){
  ((MFPrinterface*)pPrinter)->printInfo("x="+std::to_string(vector.x)+
      " y="+std::to_string(vector.y)+
      " z="+std::to_string(vector.z)+
      " w="+std::to_string(vector.w),printerIndex);
}
