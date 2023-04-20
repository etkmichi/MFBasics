/*
 * MFBasicDefines.h
 *
 *  Created on: 20.01.2021
 *      Author: michl
 */

#ifndef MFBASICDEFINES_H_
#define MFBASICDEFINES_H_
#include "MFObjects/MFObject.h"
#include "MFStringHelpers/MFToString.h"
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

#define PRINT_INF(x) MFObject::printInfo(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))

#define PRINT_WRN(x) MFObject::printWarning(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))

#define PRINT_ERR(x) MFObject::printErr(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))

#define P_INF(x) MFObject::printInfo(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))
#define P_INF_C(x,y) MFObject::printInfo(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x),y)

#define P_WRN(x) MFObject::printWarning(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))

#define P_ERR(x) MFObject::printErr(\
    std::string(__FILE__)+":"+std::to_string(__LINE__)+" "+std::string(__func__)+" - "+\
    std::string(x))

#define TO_STRING(x) MFToString::toString(x)

#define P_NUM(x) P_INF(T_S(x))

#define T_S(x) MFToString::toString(x)
#define T_HEX_S(x) MFToString::toHexString(x)


#define T_S_V3(v3) MFToString::toString(v3)

#define V3(x,y,z) glm::vec3(x,y,z)
#define V3X(x) glm::vec3(x,0,0)
#define V3Y(y) glm::vec3(0,y,0)
#define V3Z(z) glm::vec3(0,0,z)
#define V3A(all) glm::vec3(all,all,all)
#define V4(x,y,z,w) glm::vec3(x,y,z,w)
#define V4X(x) glm::vec4(x,0,0,0)
#define V4Y(y) glm::vec4(0,y,0,0)
#define V4Z(z) glm::vec4(0,0,z,0)
#define V4W(w) glm::vec4(0,0,0,w)
#define V4A(all) glm::vec4(all,all,all,all)
#define V4Red glm::vec4(1,0,0,1)
#define V4Grn glm::vec4(0,1,0,1)
#define V4Blu glm::vec4(0,0,1,1)
#define V4Tur glm::vec4(0,1,1,1)
#define V4Yel glm::vec4(1,1,0,1)
#define V4Blk glm::vec4(0,0,0,0)
#define V4Gry glm::vec4(.5f,.5f,.5f,1)
#define V4Wht glm::vec4(1,1,1,1)
#define V4Vlt glm::vec4(1,0,1,1)
#define V4Rnd glm::vec4(glm::linearRand(0,1),glm::linearRand(0,1),glm::linearRand(0,1),1)

#endif /* MFBASICDEFINES_H_ */
