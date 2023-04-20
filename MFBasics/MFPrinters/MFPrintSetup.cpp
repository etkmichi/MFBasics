/*
 * MFPrintSetup.cpp
 *
 *  Created on: 04.09.2020
 *      Author: michl
 */

#include "MFPrintSetup.h"

MFPrintSetup::MFPrintSetup() {
  // TODO Auto-generated constructor stub

}

MFPrintSetup::~MFPrintSetup() {
  // TODO Auto-generated destructor stub
}


void MFPrintSetup::printInfo(const std::string& info){
  MFObject::printInfo(info,0);
  MFObject::printInfo(info,m_printIndex);
}
void MFPrintSetup::printWarning(const std::string& warning){
  MFObject::printWarning(warning,0);
  MFObject::printWarning(warning,m_printIndex);
}
void MFPrintSetup::printErr(const std::string& err){
  MFObject::printErr(err,0);
  MFObject::printErr(err,m_printIndex);
}
