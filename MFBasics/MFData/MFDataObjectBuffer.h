/*
 * MFDataObjectBuffer.h
 *
 *  Created on: 21.02.2020
 *      Author: michl
 */

#ifndef MFDATA_MFDATAOBJECTBUFFER_H_
#define MFDATA_MFDATAOBJECTBUFFER_H_
#include <mutex>
#include "../MFObjects/MFObject.h"
#include "MFDataObject.h"

/**
 * This class provides data objects, which point to a part of a big buffer.
 */
class MFDataObjectBuffer {
  std::mutex
  lockBuffer,
  lockBufferWrite;

  uint64_t
  m_bufferByteSize=0,
  m_bufferByteOffset=0;

  std::vector<MFDataObject*>
  *mp_vecDataObjects,//TODO set childs of mp_dataObjectBuffer
  *mp_vecInternalDataObjects,
  *mp_vecExternalDataObjects;

  void
  *mp_buffer=nullptr,
  *mp_internalBuffer=nullptr,
  *mp_externalBuffer=nullptr;

  MFDataObject
  *mp_dataObjectBuffer;

  bool
  m_isCreated=false;
public:
  MFDataObjectBuffer();
  MFDataObjectBuffer(uint64_t bufferByteSize);
  virtual ~MFDataObjectBuffer();
  bool createBuffer();

  bool recreateBuffer(){
    MFObject::printErr("MFDataObjectBuffer::recreateBuffer() - no impl.!");
    return false;
  };

  /**
   * Creates a data object with the given byte size. This class will keep track
   * of the returned object and delete it in its destructor. Use
   * getNextDataObject(MFDataObject* dataObject), if the object shall not be deleted.
   * If this object is destructed, memory will be freed and the data pointer hold
   * by all returned MFDataObject will be invalidated!
   * @param byteSize
   * @return
   */
  MFDataObject* getNextDataObject(uint64_t byteSize);

  /**
   * Sets the data pointer of dataObject to this buffers memory. Copies data of dataObject
   * (if not nullptr) to the buffer. Returns true if successfull.
   * TODO what if mp_buffer is deleted?
   * @param dataObject
   * @return false if buffer is not big enough for the data.
   */
  bool setupDataObject(MFDataObject* dataObject);
  bool isFull();
  bool isCreated(){return m_isCreated;};
  bool isUsable(){return m_isCreated;};

  void* getBuffer(){return mp_buffer;};
  /**
   *
   * @return a MFDataObject which contains the whole buffer.
   */
  MFDataObject* getDataObjectBuffer(){return mp_dataObjectBuffer;};

  void setBuffer(void* pBuffer){mp_buffer=pBuffer;};

  void setBufferByteSize(uint64_t bufferByteSize){m_bufferByteSize=bufferByteSize;};
  uint64_t getBufferByteSize(){return m_bufferByteSize;};

  void setBufferOffset(const uint64_t &offset){m_bufferByteOffset=offset;};
  uint64_t getBufferByteOffset(){return m_bufferByteOffset;};
  std::vector<MFDataObject*>* getDataObjects(){return mp_vecDataObjects;};
  std::vector<MFDataObject*>* getInternalDataObjects(){return mp_vecInternalDataObjects;};
  std::vector<MFDataObject*>* getExternalDataObjects(){return mp_vecExternalDataObjects;};
};

#endif /* MFDATA_MFDATAOBJECTBUFFER_H_ */
