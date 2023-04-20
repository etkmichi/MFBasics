/*
 * MFToString.h
 *
 *  Created on: 09.02.2021
 *      Author: michl
 */

#ifndef MFSTRINGHELPERS_MFTOSTRING_H_
#define MFSTRINGHELPERS_MFTOSTRING_H_

#include <string>
#include <glm/glm.hpp>

class MFToString {
public:
  MFToString();
  virtual ~MFToString();
  static std::string toString(float scalar);
  static std::string toString(double scalar);
  static std::string toString(bool scalar);
  static std::string toString(uint32_t scalar);
  static std::string toString(uint64_t scalar);
  static std::string toString(int32_t scalar);
  static std::string toString(int64_t scalar);
  static std::string toHexString(uint64_t value);
  static std::string toString(const glm::vec3 &vec3);
  static std::string toString(const glm::vec2 &vec2);
  static std::string toString(const glm::vec4 &vec4);
  static std::string toString(const glm::mat4 &mat4);
};

#endif /* MFSTRINGHELPERS_MFTOSTRING_H_ */
