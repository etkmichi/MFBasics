/*
 * MFIStructSource.h
 *
 *  Created on: 06.04.2020
 *      Author: michl
 */

#ifndef MFDATA_MFINTERFACESDATA_MFIBUFFERSOURCE_H_
#define MFDATA_MFINTERFACESDATA_MFIBUFFERSOURCE_H_
#include "../MFStructurableData.h"

class MFIBufferSource {
public:
	virtual ~MFIBufferSource(){};
	virtual MFStructurableData* takeData(){return nullptr;};
};

#endif /* MFDATA_MFINTERFACESDATA_MFIBUFFERSOURCE_H_ */
