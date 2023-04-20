/*
 * MFTickCounter.h
 *
 *  Created on: 31.01.2020
 *      Author: michl
 */

#ifndef MFTIME_MFTICKCOUNTER_H_
#define MFTIME_MFTICKCOUNTER_H_
#include "MFTimeStructs.h"
#include "../MFBasicDefines.h"

class MFTickCounter {//TODO implement subclasses with extended measures
	//	- With auto average reset
	//	- With extra analysis record and functionality
	// TODO implement static start(&float) stop(float start,float &duration)
	//overload stop with stop(&float) - with the start as param which
	//will be overwritten with the duration value
private:
	U_TimePoint
		m_timestampCreation,
		m_timestampStart,
		m_timestampStop,
		m_timestampNow;

	int64_t
		m_duration=0,//changed from float to int64!
		m_checkDuration=0;//TODO bool check...

	double
		m_durationSum=.0,
		m_average=.0;

	uint64_t
		m_timestampSumCounter=0;

public:
	MFTickCounter();
	virtual ~MFTickCounter();

	/**
	 * Resets the measurement time point to now. If stop is called, it will return
	 * the milliseconds from start() till stop() call.
	 */
	void start();

	/**
	 * Returns the passed milliseconds since last start() call. Multiple calls to stop
	 * are allowed.
	 * @return
	 */
	int64_t stop();
	double getAverage();
	uint64_t getCPUTicker();
	void resetAverageCalculation();
	/**
	 * static function returning current ticks which represent now. With millisSince time can be
	 * measured.
	 * @return
	 */
	static int64_t current();
	static int64_t millisSince(const int64_t &timePoint);
  static int64_t ticksSince(int64_t timePoint);
	//
//	MillisDuration dur(timepoint);
//	m_sleepUntil=TimePoint(dur);
//	std::time_t t=m_sleepUntil.time_since_epoch().count();
//	MFObject::printInfo("Debug MFTaskThread::setSleepUntil - \ntime point: "+
//	std::to_string(m_sleepUntil.time_since_epoch().count())+"\nparameter: "+
//	std::to_string(timepoint)+"\nreadable time:"+
//	std::string(std::ctime(&t)));
  /**
   * test if timeout is eql than time in millis since timepoint. If to is exceeded, it will
   * set tp to current and return true!
   * @param to - timeout in milliseconds
   * @param tp - timepoint
   * @return
   */
  static bool tt(const int64_t &to,int64_t &tp);

};

#endif /* MFTIME_MFTICKCOUNTER_H_ */
