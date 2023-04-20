/*
 * MFConfigValue.cpp
 *
 *  Created on: 29.07.2019
 *      Author: michl
 */

#include "MFConfigValue.h"

MFConfigValue::MFConfigValue(std::string name, int value){
	m_dataName=name;
	m_valInt=value;
	m_dataType=ConfigValueType::CVT_NUMBER_INT;
	m_valFloat=0;
}
MFConfigValue::MFConfigValue(std::string name, std::string value){
	m_dataName=name;
	m_valString=value;
	m_dataType=ConfigValueType::CVT_TEXT;
	m_valInt=0;
	m_valFloat=0;

}
MFConfigValue::MFConfigValue(std::string name, float value){
	m_dataName=name;
	m_valFloat=value;
	m_dataType=ConfigValueType::CVT_NUMBER_FLOAT;
	m_valInt=0;

}
MFConfigValue::~MFConfigValue() {
	// TODO Auto-generated destructor stub
}

