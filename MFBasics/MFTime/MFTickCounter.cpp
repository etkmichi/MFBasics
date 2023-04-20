/*
 * MFTickCounter.cpp
 *
 *  Created on: 31.01.2020
 *      Author: michl
 */

#include "MFTickCounter.h"

MFTickCounter::MFTickCounter() {
	m_timestampCreation=U_Clock::now();
	m_timestampStart=U_Clock::now();
	m_timestampStart-=(U_ClockDuration(10000));
	m_timestampStop=U_Clock::now();
	m_timestampNow=U_Clock::now();
}

MFTickCounter::~MFTickCounter() {
	// TODO Auto-generated destructor stub
}

uint64_t MFTickCounter::getCPUTicker(){
	uint32_t lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((int64_t)hi<<32)|lo;
}

void MFTickCounter::start(){
	m_timestampStart=U_Clock::now();
	if(m_duration>.0f){
		m_timestampSumCounter++;
		m_durationSum+=m_duration;
	}
}

int64_t MFTickCounter::stop(){
	m_timestampStop=U_Clock::now();

	m_duration=U_MillisDuration(
			m_timestampStop-m_timestampStart).count();
	return m_duration;
}

double MFTickCounter::getAverage(){
	if(m_timestampSumCounter==0)return stop();
	m_average=(m_durationSum/m_timestampSumCounter);
	return m_average;
}

void MFTickCounter::resetAverageCalculation(){
	m_timestampSumCounter=0;
	m_average=0;
}

int64_t MFTickCounter::current(){
	U_TimePoint yet=U_Clock::now();
	int64_t duration=yet.time_since_epoch().count();//U_ClockDuration(yet-yet.min()).count();
	return duration;
}

int64_t MFTickCounter::millisSince(const int64_t &timePoint){
	U_TimePoint yet=U_Clock::now();
	int64_t tillNowDuration=yet.time_since_epoch().count();//U_ClockDuration(yet-yet.min()).count();
	int64_t span=tillNowDuration-timePoint;
	/*one tick equals 1ns -> return millis!*/
	span/=1000000;
	return span;
}
int64_t MFTickCounter::ticksSince(int64_t timePoint){
  U_TimePoint yet=U_Clock::now();
  int64_t span=yet.time_since_epoch().count()-timePoint;
  /*one tick equals 1ns -> return millis!*/
  return span;
}

bool MFTickCounter::tt(const int64_t &to,int64_t &tp){
  int64_t passedMillis=MFTickCounter::millisSince(tp);
  if((passedMillis >= to)){
    tp=MFTickCounter::current();
    return true;
  }
  return false;
}
