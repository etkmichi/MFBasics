/*
 * MFPrintSetup.h
 *
 *  Created on: 04.09.2020
 *      Author: michl
 */

#ifndef MFPRINTERS_MFPRINTSETUP_H_
#define MFPRINTERS_MFPRINTSETUP_H_
#include "../MFObjects/MFObject.h"
class MFPrintSetup {
public:
  uint32_t
  m_printIndex=0;
  MFPrintSetup();
  virtual ~MFPrintSetup();
  void printInfo(const std::string& info);
  void printWarning(const std::string& warning);
  void printErr(const std::string& err);
};

#endif /* MFPRINTERS_MFPRINTSETUP_H_ */
