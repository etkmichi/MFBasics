/*
 * MFIDataObjectWrite.h
 *
 *  Created on: 24.03.2020
 *      Author: michl
 */

#ifndef MFDATA_MFIDATAOBJECTWRITE_H_
#define MFDATA_MFIDATAOBJECTWRITE_H_
#include <stdint.h>
class MFIDataObjectWrite {
public:
	MFIDataObjectWrite();
	virtual ~MFIDataObjectWrite();
	virtual bool writeData(
			void* pDestination,
			void* pInput,
      const uint32_t &dataByteSize);
  virtual bool writeData(
      void* pDestination,
      const void* pInput,
      const uint32_t &dataByteSize);
	//TODO check how read can be implemented, use existing implementations
};

#endif /* MFDATA_MFIDATAOBJECTWRITE_H_ */
