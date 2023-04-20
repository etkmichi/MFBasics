/*
 * MFStructurableData.h
 *
 *  Created on: 17.03.2020
 *      Author: michl
 */

#ifndef MFDATA_MFSTRUCTURABLEDATA_H_
#define MFDATA_MFSTRUCTURABLEDATA_H_
#include "MFDataObject.h"
#include "MFDataObjectBuffer.h"
#include "../MFObjects/MFObject.h"
/**
 * This class provides a strucurable data setup for custom objects.
 * TODO extend all add functions and use shared buffer function with data groups. Use default
 * group for compatiblity with already implemented structures.
 * -> Data groups shall provide header data separation -> header size and periodically added data
 * -> Grouping data provides more efficient data structures for graphics and physics calculation
 * 		bc. unused data like headers can be separated and often used data like model matrix can
 * 		be allocated at one piece without header data between.
 * 		TODO point out that a pointer to a value given as parameter of an add function will
 * 		be used for storing data. (uint32_t data=0; addData(&data); -> pointer to data will be
 * 		used within this object, some times this is not what so wants...
 */
class MFStructurableData {
private:
  std::string
  m_name;
public:
  const std::string& getStructureName(){
    return m_name;
  }
  void setStructureName(const std::string &name){
    m_name=name;
  }
private:
  uint32_t
  m_dataSize=0;

  MFDataObjectBuffer
  *mp_sharedBuffer=nullptr;
  std::vector<MFDataObject*>
  *mp_vecDataCollection,
  *mp_vecInternalData;
protected:

  inline void setupSharedBufferData(MFDataObject* pData);
  //TODO use separated shared buffers
  //-> for each data type added, use a separated buffer
  //-> set shared buffer for data at specific index
  //-> better usage, if some data are not important during processing, this data can
  // 	be separated by defining a separated shared buffer.
public:
  bool
  m_printInitData=true;

  /**
   * The implementation of this function may update the objects data pointers to
   * point to the buffer data. This function should be called after all buffers are
   * allocated.
   */
  virtual void initDataPointer(){};

  /**
   * Initializes the data. Depends on the implementation of MFStructurableData.
   */
  virtual void initData(){
    if(m_printInitData)
      MFObject::printWarning("MFStructurableData::initData - "
          "No implementation!");
  };
public:
  MFStructurableData();
  virtual ~MFStructurableData();

  /**
   * Adds a new data object which is filled with the informations of typeInfo.
   * @param typeInfo
   * @return
   */
  MFDataObject* addData(MFDataObject &typeInfo);

  /**
   * Adds data which was created somewhere else (no copy will be made, except a shared buffer
   * shall be used). The data will be deleted by the constructor of this class!
   * /TODO create internal data for deletion and add bool deleteByDest to the params
   * @warning this data will be deleted during destruction of this object!!
   * @param pData
   */
  void addData(MFDataObject* pData,bool deleteByDestructor=true);

  /**
   * Adds three 32Bit values (must be one sequence in memory) as one data pointer of
   * type 3d vector.
   * @param data
   * @return
   */
  MFDataObject* add3DVec(void* data);
  MFDataObject* add2DVec(void* data);
  MFDataObject* addData(double* data){return add64BitValue(DATA_TYPE_DOUBLE64, data);};
  MFDataObject* addData(float* data){return add32BitValue(DATA_TYPE_FLOAT32, data);};
  MFDataObject* addData(uint64_t* data){return add64BitValue(DATA_TYPE_UINT64, data);};
  MFDataObject* addData(int64_t* data){return add64BitValue(DATA_TYPE_INT64, data);};
  MFDataObject* addData(uint32_t* data){return add32BitValue(DATA_TYPE_UINT32, data);};
  MFDataObject* addData(int32_t* data){return add32BitValue(DATA_TYPE_INT32, data);};
  MFDataObject* addData(uint16_t* data){return add16BitValue(DATA_TYPE_UINT16, data);};
  MFDataObject* addData(int16_t* data){return add16BitValue(DATA_TYPE_INT16, data);};
  MFDataObject* addData(uint8_t* data){return add8BitValue(DATA_TYPE_UINT8, data);};
  MFDataObject* addData(int8_t* data){return add8BitValue(DATA_TYPE_INT8, data);};
  MFDataObject* addData(void** data){return add64BitDataPointer(data);};
  MFDataObject* add64BitDataPointer(void** data);
  MFDataObject* add64BitValue(E_DataType subType,void* data);
  MFDataObject* add32BitValue(E_DataType subType,void* data);
  MFDataObject* add16BitValue(E_DataType subType,void* data);
  MFDataObject* add8BitValue(E_DataType subType,void* data);
  MFDataObject* addNBitValue(uint32_t bitCount,void* data);
  MFDataObject* add4x4Matrix(void* data);
  std::vector<MFDataObject*>* getVecData(){return mp_vecDataCollection;};

  /**
   * Clears the data and adds the data provided by pExternalData.
   * @param pExternalData
   */
  void importDataStructure(MFStructurableData* pExternalData);

  /**
   * Appends the given data structure to this data structure. If a shared buffer
   * is used, data will be copied to the buffer. If no shared buffer is used,
   * the appended data will point to the same buffers as pAppendable.
   * @param pAppendable structure to copy from
   */
  void appendDataStructure(MFStructurableData* pAppendable);

  /**
   * This function returns the data pointer to the data part of the package.
   * @warning if no shared buffer was used,
   * you must not access memory after first data entry!
   * @return the data pointer of the first entry.
   */
  void* getStructureData();

  /**
   * This function writes the internal data to dst_buffer. If some data are nullptr,
   * it will skip copying and print a warning. If this object was set up with a
   * shared buffer, it will copy the data in one piece, if the data was not set
   * up with a shared buffer, it will iterate over sub data and copy its content.
   * @param dst_buffer - destination buffer for copying the added data.
   * @param dst_offset offset into the dst_buffer
   * @return
   */
  bool copyDataFromStructure(void* dst_buffer,uint32_t dst_offset);

  bool copyDataToStructure(void* src_buffer,uint32_t src_offset);

  bool copyDataToStructure(void* src_buffer,uint32_t src_offset,uint32_t length);

  /**
   * Deletes all data entries and clears the vector!
   */
  void clear();

  uint32_t calculateStructureSize();

  uint32_t getStructureSize(){return m_dataSize;};
  /**
   * This will overwrite the over all structure size, try not to do this!
   * @param size
   * @return
   */
  void setStructureSize(uint32_t size){m_dataSize=size;};

  void printMetaData();

  /**
   * If shared data is used, all data will be added to the pSharedBuffer.
   * All returned MFDataObject* will use memory from the pSharedBuffer if set.
   * All added data will be copied to the pSharedBuffer memory.
   * @param pSharedBuffer
   */
  void useSharedBuffer(MFDataObjectBuffer* pSharedBuffer);

  /**
   * This will free all data and set the corresponding MFDataObject's data pointer to null.
   * Take care that the buffers which will be freed arnt used sw else! Data structure will
   * remain only data pointers of sub data will be freed and set to null!
   */
//  void freeData();
  MFDataObjectBuffer* getSharedBuffer(){
    return mp_sharedBuffer;
  }
};

#endif /* MFDATA_MFSTRUCTURABLEDATA_H_ */
