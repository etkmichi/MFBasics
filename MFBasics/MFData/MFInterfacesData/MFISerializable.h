/*
 * MFISerializable.h
 *
 *  Created on: 27.04.2020
 *      Author: michl
 */

#ifndef MFDATA_MFINTERFACESDATA_MFISERIALIZABLE_H_
#define MFDATA_MFINTERFACESDATA_MFISERIALIZABLE_H_
#include "../../MFObjects/MFObject.h"
#include "../MFDataObject.h"
class MFISerializable {
	uint64_t
		m_serializerID;
public:
	MFISerializable(uint64_t serializerID){
		m_serializerID=serializerID;
		MFObject::printErr("MFISerializable:No implementation!");
	};
	virtual ~MFISerializable();
	void addData(){};
	virtual MFDataObject* serialize(void* in_data, uint64_t dataSize);
};

#endif /* MFDATA_MFINTERFACESDATA_MFISERIALIZABLE_H_ */
