/*
 * MFIDataObjectWrite.cpp
 *
 *  Created on: 24.03.2020
 *      Author: michl
 */

#include "MFIDataObjectWrite.h"
#include "../../MFObjects/MFObject.h"
MFIDataObjectWrite::MFIDataObjectWrite() {

}

MFIDataObjectWrite::~MFIDataObjectWrite() {
}
bool MFIDataObjectWrite::writeData(
                        void* pDestination,
                        void* pInput,
                        const uint32_t &dataByteSize){
    MFObject::printErr("MFIDataObjectWrite::writeData - no impl.!");
    return false;};
bool MFIDataObjectWrite::writeData(
                        void* pDestination,
                        const void* pInput,
                        const uint32_t &dataByteSize){
    MFObject::printErr("MFIDataObjectWrite::writeData - no impl.!");
    return false;};
