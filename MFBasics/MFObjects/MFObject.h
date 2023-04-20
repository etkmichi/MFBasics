/*
 * MFObject.h
 *
 *  Created on: 09.07.2019
 *      Author: michl
 */

#ifndef MFOBJECTS_MFOBJECT_H_
#define MFOBJECTS_MFOBJECT_H_
#include <string>
#include <glm/glm.hpp>
class MFObject {
public:
  static void* pPrinter;
	MFObject();
	virtual ~MFObject();
	static void printErr(const std::string& txt,const uint32_t &printerIndex=0);
	static void printWarning(const std::string& txt,const uint32_t &printerIndex=0);
	static void printInfo(const std::string& txt,const uint32_t &printerIndex=0);
	static void printVec3(const glm::vec3& vector,const uint32_t &printerIndex=0);
  static void printVec4(const glm::vec4& vector,const uint32_t &printerIndex=0);

//	static MFPrinterface& getPrinterface(){return printer;};
};

#endif /* MFOBJECTS_MFOBJECT_H_ */
