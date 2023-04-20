/*
 * MFTimeStructs.h
 *
 *  Created on: 08.04.2020
 *      Author: michl
 */

#ifndef MFTIME_MFTIMESTRUCTS_H_
#define MFTIME_MFTIMESTRUCTS_H_
#include <chrono>
#include <time.h>
	using U_Millis=std::chrono::milliseconds;
	using U_Seconds=std::chrono::seconds;
	using U_MillisDuration=std::chrono::duration<double, U_Millis::period>;
	using U_Clock=std::chrono::system_clock;
	using U_ClockDuration=U_Clock::duration;
	using U_TimePoint=std::chrono::time_point<U_Clock,U_ClockDuration>;



#endif /* MFTIME_MFTIMESTRUCTS_H_ */
