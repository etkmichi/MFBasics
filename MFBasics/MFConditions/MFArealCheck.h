/*
 * MFArealCheck.h
 *
 *  Created on: 17.11.2020
 *      Author: michl
 */

#ifndef MFCONDITIONS_MFAREALCHECK_H_
#define MFCONDITIONS_MFAREALCHECK_H_

#include "MFBaseCondition.h"
#include <glm/glm.hpp>
/**
 * This class provides to define a space by reimplementing the
 * check(glm::vec3) function. Default implementation will check if given
 * postion is within a sphere.
 *
 */
class MFArealCheck: public MFBaseCondition {
private:
  float
  m_radius;

  glm::vec3
  m_currentPoint,
  m_position,
  *mp_externalPosition;
protected:/*virtual functions MFBaseCondition*/
  virtual bool internalCheck(){return checkPoint(m_currentPoint);};

public:/*virtual functions of MFArealCheck*/
  virtual bool checkPoint(const glm::vec3 &position);

public:
  MFArealCheck();
  virtual ~MFArealCheck();
  void setDefaultCheckRadius(float radius){m_radius=radius;};
  void setExternalPosition(glm::vec3 *pPosition){mp_externalPosition=pPosition;};
};

#endif /* MFCONDITIONS_MFAREALCHECK_H_ */
