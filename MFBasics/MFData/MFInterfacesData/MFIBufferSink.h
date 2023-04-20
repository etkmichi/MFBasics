/*
 * MFIStructSink.h
 *
 *  Created on: 06.04.2020
 *      Author: michl
 */

#ifndef MFDATA_MFINTERFACESDATA_MFIBUFFERSINK_H_
#define MFDATA_MFINTERFACESDATA_MFIBUFFERSINK_H_
#include "../MFStructurableData.h"
class MFIBufferSink {
public:
	virtual ~MFIBufferSink(){};
	virtual bool returnData(MFStructurableData* pData){
		MFObject::printErr("MFIStructSink::returnData - no implementation!");
		return false;
	};
};

#endif /* MFDATA_MFINTERFACESDATA_MFIBUFFERSINK_H_ */
