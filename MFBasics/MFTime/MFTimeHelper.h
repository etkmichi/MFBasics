/*
 * MFTimeHelper.h
 *
 *  Created on: 26.08.2020
 *      Author: michl
 */

#ifndef MFTIME_MFTIMEHELPER_H_
#define MFTIME_MFTIMEHELPER_H_
#include "MFTimeStructs.h"
#include <iostream>
class MFTimeHelper {
public:
  MFTimeHelper();
  virtual ~MFTimeHelper();
  static std::string toString(U_TimePoint &tp,bool withMillis=true){
    U_Seconds secnds=MFTimeHelper::getSeconds(tp);
    std::time_t secs=secnds.count();
    std::string time=std::string(std::ctime(&secs));
    std::string time2=std::string(time.data(),time.length()-6);
    if(withMillis){
      U_Millis millis=MFTimeHelper::getMillis(tp);
      uint32_t mils=millis.count()%1000;
      time2+=" ("+std::to_string(mils)+"ms)";
    }
    return time2;
  }

  static U_Millis getMillis(U_TimePoint &tp){
    U_Millis millis=std::chrono::duration_cast<U_Millis>(
        tp.time_since_epoch());
    return millis;
  }

  static U_Seconds getSeconds(U_TimePoint &tp){
    U_Seconds scd=std::chrono::duration_cast<U_Seconds>(
        tp.time_since_epoch());
    return scd;
  }

  static std::string getNowString(bool withMillis=false){
    U_TimePoint now=U_Clock::now();
    return toString(now,withMillis);
  }
};

#endif /* MFTIME_MFTIMEHELPER_H_ */
