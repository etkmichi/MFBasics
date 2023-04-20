/*
 * MFAbstractTask.h
 *
 *  Created on: 08.07.2019
 *      Author: michl
 */
#ifndef MFABSTRACTTASK_H_
#define MFABSTRACTTASK_H_

#include "../MFObjects/MFObject.h"
#include "../MFPrinters/MFPrintSetup.h"
#include <mutex>
#include <iostream>
#include <chrono>

class MFAbstractTask : public MFPrintSetup{
protected:
  std::string
  m_taskName="MFAbstractTask";
private://TODO protected

  bool
  m_isDone,
  m_reDoOnFailure=false,
  m_isDeletable=false,
  m_deleteAfterExecution=false;

  std::mutex
  lockResources,
  lockTimeResources;

  int64_t
  m_timestampCreation=0,
  m_timestampExecuteStart=0,
  m_timestampExecuteStop=0,
  m_timestampNow=0,
  m_timestampSumCounter=0,
  m_minCallInterval=0,
  m_timestampExecuteSum=0,
  m_timeDuration=0,
  m_timeLatestExecution=1.0,
  m_pauseTime=0;

public:/*virtual functions of MFAbstractTask*/
  virtual bool doWork();

  virtual bool undoWork();

public:
  uint32_t
  m_taskManagerID=0,
  m_taskIndex=0;

  MFAbstractTask();

  void setTaskName(const std::string &name){
    m_taskName=name;
  }

  std::string getTaskName(){
    return m_taskName;
  }

  virtual ~MFAbstractTask();

  bool execute();

  bool isDone();

  /**
   * The given time in milliseconds will be paused after last execution. Depending on execution
   * call rate, the pause time may be higher than the specified millis!
   * The pause time defines the time between flank down of execution
   * (end of execution) to next flank up of execution (start of execution).
   * @param millis
   */
  void setPauseTime(int64_t millis);

  /**
   * Sets the intervall time before task will be executed again. This intervall defines
   * the time from start flank of execution to next start flank of execution. If task takes longer
   * than this intervall it will immediatly executed again if execute() is called!
   * If pause time is set, the call intervall may be ignored (if pause time + execution time is
   * higher than intervall time)!
   * @param millis
   */
  void setCallIntervall(int64_t millis){
    m_minCallInterval=millis;
  }

  void setRedoOnFailure(bool enable);

  bool redoOnFailure();

  /**
   * Calculates the time since the last execution call (time since start of execution).
   * @return count of passed milliseconds
   */
  int64_t getTimeSinceLastExecutionStart();
  /**
   * Calculates the time since the last execution call (time since end of execution).
   * @return count of passed milliseconds
   */
  int64_t getTimeSinceLastExecutionEnd();

  /**
   * This function will calculate the average execution time. It will reset the calculation values!
   * @return the average execution time[milliseconds] since last call of this function.
   */
  double getAverageExecutionTime();

  int64_t getLastExecutionTime();

  /**
   * If deleteAfterExecution is set, isDeletable() function will return true, after
   * the execute function was called (within MFTaskThread). If MFTaskThread was setup
   * to repeate tasks, this task will not be repeated!
   * @param deleteLater
   */
  void deleteAfterExecution(bool deleteTask){m_deleteAfterExecution=deleteTask;};

  bool isDeletable(){return m_isDeletable;};

  void setTaskManagerID(uint32_t taskManagerID){m_taskManagerID=taskManagerID;};

  void setTaskManagerIndex(uint32_t taskIndex){m_taskIndex=taskIndex;};

};
#endif
