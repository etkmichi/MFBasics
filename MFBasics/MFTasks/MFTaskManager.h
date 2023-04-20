/*
 * MFTaskManager.h
 *
 *  Created on: 18.03.2020
 *      Author: michl
 */

#ifndef MFTASKS_MFTASKMANAGER_H_
#define MFTASKS_MFTASKMANAGER_H_
#include <vector>
#include "MFAbstractTask.h"
#include "MFAbstractDataProcessingTask.h"
#include "../MFThreadSystem/MFTaskThread.h"
#include "MFInterfacesTasks/MFITaskProvider.h"
#include "../MFData/MFStructurableDataBuffer.h"

/**
 * This class can be used for managing tasks, it stores tasks.
 */
class MFTaskManager :
    public MFTaskThread,
    public MFITaskProvider {
protected:
  struct DispatchCollection {
    MFAbstractTask* pTask=nullptr;
    MFTaskThread* pDispatchThread=nullptr;
    MFStructurableDataBuffer* pDataBuffer=nullptr;
    MFIStructurableDataCreator* pDataCreator=nullptr;
  };
  std::vector<DispatchCollection*>
  *mp_vecTasks;
private:
  std::vector<MFAbstractDataProcessingTask*>
  m_vecDeletableTasks;

  DispatchCollection
  *mp_dummyData;
  DispatchCollection* getDispatchCollection(MFAbstractTask* pTask){
    if(mp_vecTasks->at(pTask->m_taskIndex)->pTask==pTask)
      return mp_vecTasks->at(pTask->m_taskIndex);
    MFObject::printErr("DispatchCollection* MFTaskManager::getDispatchCollection - "
        "returning nullptr");
    return nullptr;
  }

public:/*virtual functions MFTaskManager*/
  /**
   * This function must be implemented to add all necessary tasks to the
   * task manager. The task must be added with the addTask function.
   * @return
   */
  virtual bool initTaskManager(){return false;};

public:
  MFTaskManager();
  virtual ~MFTaskManager();


  /**
   * Thread safe add task function.
   * @param pTask
   */
  uint32_t addTask(
      MFAbstractTask* pTask);


  /**
   * Thread safe add task function.
   * @param pTask
   */
  uint32_t addTask(
      MFAbstractTask* pTask,
      MFStructurableDataBuffer* pDataBuffer);

  /**
   * Thread safe add task function.
   * @param pTask
   */
  uint32_t addTask(
      MFAbstractTask* pTask,
      MFStructurableDataBuffer* pDataBuffer,
      MFTaskThread* pTaskThread,
      MFIStructurableDataCreator* pDataCreator);
  uint32_t addTask(
      MFAbstractDataProcessingTask* pTask,
      MFStructurableDataBuffer* pDataBuffer,
      MFTaskThread* pTaskThread);
  uint32_t addTask(
      MFAbstractDataProcessingTask* pTask,
      MFStructurableDataBuffer* pTaskDataProvider);
  void setDataBuffer(
      MFAbstractTask* pTask,
      MFStructurableDataBuffer* pDataBuffer);
  void setDispatchThread(
      MFAbstractTask* pTask,
      MFTaskThread* pDispatchThread);
  /**
   * Returns the task stored at index of taskID. If no task is available, this
   * function will return a dummy task!
   * @param taskID
   * @return
   */
  MFAbstractTask* getTask(uint16_t taskID);
  MFTaskThread* getTaskThread(MFAbstractTask* pTask);
  MFStructurableDataBuffer* getDataBuffer(MFAbstractTask* pTask);
  MFIStructurableDataCreator* getDataCreator(MFAbstractTask* pTash);

  /**
   * Adds a task which will be deleted during destruction of this object.
   * @param pTask
   */
  void addDeletableTask(MFAbstractDataProcessingTask* pTask);

  /**
   * Helper function for registrating a task to a MFTaskManager
   * @param pTaskProvider - a MFTaskManager object which shall provide access for pTask
   * @param dataCount - count of data for buffering. Pre allocated data which is
   * used for adding data to a task.
   * @param pTask - task which will be added to pTaskProvider with the pre-allocated
   * data
   * @param pTaskDataCreator - creator for the buffer data (pre-allocated data).
   * @param externalTaskIndex - the task index within the task manager will be written to this parameter
   * @param addToDeletableTasks - adds the task for deletion to pTaskProvider's
   * deletable tasks. pTask will be deleted in destructor of pTaskProvider.
   */
  static void updateTaskProvider(
      MFTaskManager *pTaskProvider,
      uint32_t dataCount,
      MFAbstractDataProcessingTask* pTask,
      MFIStructurableDataCreator* pTaskDataCreator,
      uint32_t &externalTaskIndex,
      bool addToDeletableTasks=true){
    MFStructurableDataBuffer *pStructurableDataBuffer;
    MFIStructurableDataCreator *pDataCreator=pTaskDataCreator;

    pStructurableDataBuffer = new MFStructurableDataBuffer(
        pDataCreator,
        dataCount);
    pStructurableDataBuffer->initBuffer();
    pTask->setTaskManagerIndex(pTaskProvider->addTask(pTask,pStructurableDataBuffer));

    externalTaskIndex=pTask->getTaskManagerIndex();
    pTask->setBufferSink(pStructurableDataBuffer);

    if(addToDeletableTasks)
      pTaskProvider->addDeletableTask(pTask);
  }

  /**
   * Helper function for registrating a task to a MFTaskManager
   * @param pTaskProvider - a MFTaskManager object which shall provide access for pTask
   * @param dataCount - count of data for buffering. Pre allocated data which is
   * used for adding data to a task.
   * @param pTask - task which will be added to pTaskProvider with the pre-allocated
   * data
   * @param pTaskDataCreator - creator for the buffer data (pre-allocated data).
   * @param addToDeletableTasks - adds the task for deletion to pTaskProvider's
   * deletable tasks. pTask will be deleted in destructor of pTaskProvider.
   */
  static void updateTaskProvider(
      MFTaskManager *pTaskProvider,
      uint32_t dataCount,
      MFAbstractDataProcessingTask* pTask,
      MFIStructurableDataCreator* pTaskDataCreator,
      bool addToDeletableTasks=true){
    MFStructurableDataBuffer *pStructurableDataBuffer;
    MFIStructurableDataCreator *pDataCreator=pTaskDataCreator;

    pStructurableDataBuffer = new MFStructurableDataBuffer(
        pDataCreator,
        dataCount);
    pStructurableDataBuffer->initBuffer();
    pTask->setTaskManagerIndex(pTaskProvider->addTask(pTask,pStructurableDataBuffer));
    pTask->setBufferSink(pStructurableDataBuffer);

    if(addToDeletableTasks)
      pTaskProvider->addDeletableTask(pTask);
  }
};

#endif /* MFTASKS_MFTASKMANAGER_H_ */
