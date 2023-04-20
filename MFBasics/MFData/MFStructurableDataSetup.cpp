/*
 * MFStructurableDataSetup.cpp
 *
 *  Created on: 24.03.2020
 *      Author: michl
 */

#include "MFStructurableDataSetup.h"
#include "../MFObjects/MFObject.h"

MFStructurableDataSetup::MFStructurableDataSetup() {
}

MFStructurableDataSetup::~MFStructurableDataSetup() {
}

bool MFStructurableDataSetup::loadSetup(MFStructurableData* pdata){
	importDataStructure(pdata);
	return true;
}
