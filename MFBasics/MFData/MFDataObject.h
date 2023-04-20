/*
 * MFDataObject.h
 *
 *  Created on: 03.12.2019
 *      Author: michl
 */

#ifndef MFDATA_MFDATAOBJECT_H_
#define MFDATA_MFDATAOBJECT_H_
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include "MFInterfacesData/MFIDataObjectWrite.h"

enum E_GuiElement{
  GUI_TYPE_NONE,
  GUI_TYPE_SLIDER,
  GUI_TYPE_BUTTON,
  GUI_TYPE_TEXT_VIEW,
  GUI_TYPE_TEXT_EDIT,
  GUI_TYPE_NUMBER_VIEW,
  GUI_TYPE_NUMBER_EDIT,
  GUI_TYPE_SPIN_BOX,
  GUI_TYPE_DROP_DOWN_MENU,
  GUI_TYPE_LIST,
  GUI_TYPE_4D_VEC,
  GUI_TYPE_3D_VEC,
  GUI_TYPE_2D_VEC,
  GUI_TYPE_MATRIX,
  GUI_TYPE_MATRCES,
  GUI_TYPE_BIT_VIEW,
  GUI_TYPE_IPV4_EDIT,
  GUI_TYPE_IPV4_VIEW,
  GUI_TYPE_PORT_EDIT,
  GUI_TYPE_PORT_VIEW,
  GUI_TYPE_DATA_POINTER
};

//TODO better implementaiton! if a type is added, sizes may be overwritten!!!
enum E_DataType{//Do not change this enumeration!!! used by cpp file!
  DATA_TYPE_DUMMY,
  DATA_TYPE_BOOL,
  DATA_TYPE_UINT8,
  DATA_TYPE_UINT16,
  DATA_TYPE_UINT32,
  DATA_TYPE_UINT64,
  DATA_TYPE_INT8,
  DATA_TYPE_INT16,
  DATA_TYPE_INT32,
  DATA_TYPE_INT64,
  DATA_TYPE_FLOAT32,
  DATA_TYPE_DOUBLE64,
  DATA_TYPE_VOID_PTR_64,
  DATA_TYPE_VEC_2D,
  DATA_TYPE_VEC_3D,
  DATA_TYPE_VEC_4D,
  DATA_TYPE_N_VEC_2D,
  DATA_TYPE_N_VEC_3D,
  DATA_TYPE_N_VEC_4D,
  DATA_TYPE_MAT_3X3,
  DATA_TYPE_MAT_4X4,
  DATA_TYPE_N_MAT_4X4,
  DATA_TYPE_STRING,
  DATA_TYPE_N_BIT
};

struct S_DataType{
  std::string name="no name";
  E_DataType type;
};

/**
 * This class is for describing data. Meta information will be stored within this
 * classes sub objects. Take care, this class uses data maps for setup and some
 * set functions, dont change or set up objects during work load (writing data or
 * using data is ok)!
 * TODO change map to vector
 */
class MFDataObject {//TODO add parent child structure with vector for childs
public:
  static void setDataTypeSize(E_DataType dataType,uint32_t size);
private:
  std::string
  m_objectName="";
  static std::vector<S_DataType>
  ms_vecTypes;
  static std::vector<uint32_t>
  *smp_vecDataSizes;//TODO add type function
  static std::mutex
  lockVecTypes;

  void
  *mp_data=nullptr,
  *mp_initialData=nullptr,
  *mp_innerData=nullptr;
  bool
  m_isStatic=false,
  m_isValid=true,
  m_writable=true,
  m_allowSharedMemory=true;

  uint32_t
  m_dataByteSize=0,
  m_dataStride=0,
  m_nBitSize=0,
  m_subGuiType,
  m_subDataType;
  E_GuiElement
  m_guiType;
  E_DataType
  m_dataType;

  std::mutex
  *mp_externalUsage;

  MFIDataObjectWrite
  *mp_writeDataInterface=nullptr;

public:
  MFDataObject();
  virtual ~MFDataObject();
  void setData(void* data){mp_data=data;};
  /**
   * Frees inner and/or external data of this MFDataObject! Take care that data is not
   * used anymore!
   */
//  void freeData();
  void setDataByteSize(uint32_t byteSize){m_dataByteSize=byteSize;};
  void setNBitSize(uint32_t nBitSize){
    m_nBitSize=nBitSize;
    m_dataByteSize=m_nBitSize/8;
  };//TODO usage for bit mask

  uint32_t getNBitSize(){return m_nBitSize;};

  void* getData(){return mp_data;}

  const uint32_t& getDataStride(){return m_dataStride;};

  void setGuiType(E_GuiElement guiRepresentation){m_guiType=guiRepresentation;};

  void setTypes(E_DataType dT,E_GuiElement gT){
    m_dataType=dT;
    m_guiType=gT;
  }

  void setDataType(E_DataType type);

  void setSubDataType(E_DataType type);

  void setSubGuiType(E_GuiElement subGuiType){m_subGuiType=subGuiType;};

  void setDataStride(uint32_t stride){m_dataStride=stride;};

  /**
   * User pointer for initial data.
   * @param data
   */
  void setInitialData(void* data){mp_initialData=data;};
  void* getInitialData(){return mp_initialData;};

  void setStatic(bool isStatic){m_isStatic=isStatic;};

  bool isStatic(){return m_isStatic;};

  void setWritable(bool writable){m_writable=writable;};

  bool isWritable(){return m_writable;};

  /**
   * The write data interface can be used for specific write implementation.
   * @param pWDI
   */
  void setWriteDataInterface(MFIDataObjectWrite* pWDI){mp_writeDataInterface=pWDI;};

  MFIDataObjectWrite* getWriteDataInterface(){return mp_writeDataInterface;};

  /**
   * Sets the valid flag to false.
   */
  void invalidate(){m_isValid=false;};

  void setObjectName(std::string name){m_objectName=name;};

  std::string getObjectName(){return m_objectName;};

  /**
   * Allocates the data within this object. With the deletion of this object,
   * the data will be freed.
   * @param dataSize
   * @return
   */
  bool allocate(uint32_t dataSize=0);

  /**
   * Writes data to this object. dataSize is used for comparing the given data
   * size with getDataByteSize(). Allocates memory for this object if the inner
   * data pointer is nullptr.
   * @param data - data to copy from
   * @param dataSize - size of the given data. Must not exceed getDataSize().
   * @return true if copying was successful. False if size doesnt match or false
   * if memcpy throws exception.
   */
  bool writeData(void* in_data,const uint32_t &dataSize);

  /**
   * Writes data to this object. Allocates memory for this object if the inner
   * data pointer is nullptr.
   * @param data - data to copy from
   * @return true if copying was successful. False
   * if memcpy throws exception.
   */
  bool writeData(void* in_data);

  /**
   * Writes data to this object. dataSize is used for comparing the given data
   * size with getDataByteSize(). Allocates memory for this object if the inner
   * data pointer is nullptr.
   * @param data - data to copy from
   * @param dataSize - size of the given data. Must not exceed getDataSize().
   * @return true if copying was successful. False if size doesnt match or false
   * if memcpy throws exception.
   */
  bool writeData(const void* in_data,const uint32_t &dataSize);

  /**
   * Writes data to this object. Allocates memory for this object if the inner
   * data pointer is nullptr.
   * @param data - data to copy from
   * @return true if copying was successful. False
   * if memcpy throws exception.
   */
  bool writeData(const void* in_data);

  /**
   * Sets the valid flag to true.
   */
  void validate(){m_isValid=true;};
  bool isValid(){return m_isValid;};

  bool isSharedMemoryAllowed(){return m_allowSharedMemory;};
  /**
   * This bool can be set for usage within buffer classes.
   * TODO check conditions for buffer class which uses shared buffer
   * TODO copying data at once is not possible if one MFDataObject is not
   * allowed to use shared buffer...
   * TODO buffer with shared buffer will be structured with a vector containing
   * the whole parts of the buffer
   * @param enable
   * @return
   */
  void allowSharedMemoryUsage(bool allow=true){m_allowSharedMemory=allow;};

  E_GuiElement& getGuiType(){return m_guiType;};
  E_DataType& getDataType(){return m_dataType;};
  uint32_t getDataSize(){return m_dataByteSize;};
  uint32_t getSizeOfType();
  void lockExternalUsage();
  void unlockExternalUsage();
  std::string toString();
  static void initDataSizes();
};

#endif /* MFDATA_MFDATAOBJECT_H_ */
