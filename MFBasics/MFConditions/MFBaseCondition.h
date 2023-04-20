/*
 * MFBaseCondition.h
 *
 *  Created on: 17.11.2020
 *      Author: michl
 */

#ifndef MFCONDITIONS_MFBASECONDITION_H_
#define MFCONDITIONS_MFBASECONDITION_H_

class MFBaseCondition {
private:
  bool
  m_invert=false;

protected:/*virtual functions MFBaseCondition*/
  virtual bool internalCheck(){return true;};

public:
  MFBaseCondition();
  virtual ~MFBaseCondition();
  void invert(bool invert){m_invert=invert;};
  bool check(){return (m_invert!=internalCheck());};
};

#endif /* MFCONDITIONS_MFBASECONDITION_H_ */
