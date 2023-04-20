/*
 * MFIStructurableDataCreator.h
 *
 *  Created on: 23.03.2020
 *      Author: michl
 */

#ifndef MFDATA_MFISTRUCTURABLEDATACREATOR_H_
#define MFDATA_MFISTRUCTURABLEDATACREATOR_H_
#include "../MFStructurableData.h"
class MFIStructurableDataCreator {
public: /*virtual functions of MFIStructurableDataCreator*/
  virtual MFStructurableData* createNewEmptyData(){
    MFObject::printWarning("MFIStructurableDataCreator::createNewEmptyData - call to "
        "empty function!");
    return nullptr;
  };

public:
	MFIStructurableDataCreator();
	virtual ~MFIStructurableDataCreator();
};

#endif /* MFDATA_MFISTRUCTURABLEDATACREATOR_H_ */
