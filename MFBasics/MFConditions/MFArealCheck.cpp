/*
 * MFArealCheck.cpp
 *
 *  Created on: 17.11.2020
 *      Author: michl
 */

#include "MFArealCheck.h"
#include <glm/gtx/norm.hpp>

MFArealCheck::MFArealCheck() {
  m_currentPoint=glm::vec3(0,0,0);
  m_position=glm::vec3(0,0,0);
  mp_externalPosition=&m_position;
  m_radius=0.0f;
}

MFArealCheck::~MFArealCheck() {
  // TODO Auto-generated destructor stub
}

bool MFArealCheck::checkPoint(const glm::vec3 &position){
  m_currentPoint=position;
  float sqdDistance=glm::distance2(*mp_externalPosition, m_currentPoint);
  if(sqdDistance<=(m_radius*m_radius)){
    return true;
  }
  return false;
}
