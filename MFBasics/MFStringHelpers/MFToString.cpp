/*
 * MFToString.cpp
 *
 *  Created on: 09.02.2021
 *      Author: michl
 */

#include "MFToString.h"
#include <iomanip>
MFToString::MFToString() {
  // TODO Auto-generated constructor stub

}

MFToString::~MFToString() {
  // TODO Auto-generated destructor stub
}

std::string MFToString::toString(const glm::vec3 &vec3){
  std::string vec=std::to_string(vec3.x)+
      "/"+std::to_string(vec3.y)+
      "/"+std::to_string(vec3.z);
  return vec;
}
std::string MFToString::toString(const glm::vec2 &vec2){
  std::string vec=std::to_string(vec2.x)+
      "/"+std::to_string(vec2.y);
  return vec;
}

std::string MFToString::toString(const glm::vec4 &vec4){
  std::string info="\n",
  x=std::to_string(vec4.x),
  y=std::to_string(vec4.y),
  z=std::to_string(vec4.z),
  w=std::to_string(vec4.w);
  uint32_t maxLength=1;
  if(x.length()>maxLength)maxLength=x.length();
  if(y.length()>maxLength)maxLength=y.length();
  if(z.length()>maxLength)maxLength=z.length();
  if(w.length()>maxLength)maxLength=w.length();
  while(x.length()<maxLength)x+=" ";
  while(y.length()<maxLength)y+=" ";
  while(z.length()<maxLength)z+=" ";
  while(w.length()<maxLength)w+=" ";
  info+=x+" | "+y+" | "+z+" | "+w;
  return info;
}
std::string MFToString::toString(const glm::mat4 &mat4){
  glm::vec4 vec4=mat4[0];
  std::string
  x0=std::to_string(vec4.x),
  y0=std::to_string(vec4.y),
  z0=std::to_string(vec4.z),
  w0=std::to_string(vec4.w);
  uint32_t maxLength=1;
  if(x0.length()>maxLength)maxLength=x0.length();
  if(y0.length()>maxLength)maxLength=y0.length();
  if(z0.length()>maxLength)maxLength=z0.length();
  if(w0.length()>maxLength)maxLength=w0.length();

  vec4=mat4[1];
  std::string
  x1=std::to_string(vec4.x),
  y1=std::to_string(vec4.y),
  z1=std::to_string(vec4.z),
  w1=std::to_string(vec4.w);
  if(x1.length()>maxLength)maxLength=x1.length();
  if(y1.length()>maxLength)maxLength=y1.length();
  if(z1.length()>maxLength)maxLength=z1.length();
  if(w1.length()>maxLength)maxLength=w1.length();

  vec4=mat4[2];
  std::string
  x2=std::to_string(vec4.x),
  y2=std::to_string(vec4.y),
  z2=std::to_string(vec4.z),
  w2=std::to_string(vec4.w);
  if(x2.length()>maxLength)maxLength=x2.length();
  if(y2.length()>maxLength)maxLength=y2.length();
  if(z2.length()>maxLength)maxLength=z2.length();
  if(w2.length()>maxLength)maxLength=w2.length();

  vec4=mat4[3];
  std::string
  x3=std::to_string(vec4.x),
  y3=std::to_string(vec4.y),
  z3=std::to_string(vec4.z),
  w3=std::to_string(vec4.w);
  if(x3.length()>maxLength)maxLength=x3.length();
  if(y3.length()>maxLength)maxLength=y3.length();
  if(z3.length()>maxLength)maxLength=z3.length();
  if(w3.length()>maxLength)maxLength=w3.length();

  while(x0.length()<maxLength)x0+=" ";
  while(y0.length()<maxLength)y0+=" ";
  while(z0.length()<maxLength)z0+=" ";
  while(w0.length()<maxLength)w0+=" ";
  while(x1.length()<maxLength)x1+=" ";
  while(y1.length()<maxLength)y1+=" ";
  while(z1.length()<maxLength)z1+=" ";
  while(w1.length()<maxLength)w1+=" ";
  while(x2.length()<maxLength)x2+=" ";
  while(y2.length()<maxLength)y2+=" ";
  while(z2.length()<maxLength)z2+=" ";
  while(w2.length()<maxLength)w2+=" ";
  while(x3.length()<maxLength)x3+=" ";
  while(y3.length()<maxLength)y3+=" ";
  while(z3.length()<maxLength)z3+=" ";
  while(w3.length()<maxLength)w3+=" ";
  std::string info="\n";
  info+=x0+" | "+y0+" | "+z0+" | "+w0+"\n";
  info+=x1+" | "+y1+" | "+z1+" | "+w1+"\n";
  info+=x2+" | "+y2+" | "+z2+" | "+w2+"\n";
  info+=x3+" | "+y3+" | "+z3+" | "+w3+"\n";
  return info;
}
std::string MFToString::toString(float scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(double scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(bool scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(uint32_t scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(uint64_t scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(int32_t scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toString(int64_t scalar){
  std::string info=std::to_string(scalar);
  return info;
}
std::string MFToString::toHexString(uint64_t value){
  std::stringstream stream;
  stream << std::hex << value;
  return stream.str();
}
