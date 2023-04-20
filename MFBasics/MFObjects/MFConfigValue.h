/*
 * MFConfigValue.h
 *
 *  Created on: 29.07.2019
 *      Author: michl
 */

#ifndef MFOBJECTS_MFCONFIGVALUE_H_
#define MFOBJECTS_MFCONFIGVALUE_H_
#include <string>
/**
 * This class can be used for default configurations. The default configs can be changed during runtime or start of a programm.
 * Example: load a specific configuration from a database and change the static MFConfigValue variables in the program according to the loaded
 * data.
 */
class MFConfigValue {
	enum ConfigValueType{
		CVT_TEXT,
		CVT_NUMBER_INT,
		CVT_NUMBER_FLOAT,
		CVT_NUMBER_DOUBLE,
		CVT_ENUMERATION,
		CVT_TIME_HHMMYY,
		CVT_TIME_STAMP,
		CVT_SIZE
	};
private:
	int m_valInt;
	std::string
		m_valString,
		m_dataName;
	float m_valFloat;
	ConfigValueType m_dataType;
public:
	MFConfigValue(std::string name, int value);
	MFConfigValue(std::string name, std::string value);
	MFConfigValue(std::string name, float value);
	virtual ~MFConfigValue();
};

#endif /* MFOBJECTS_MFCONFIGVALUE_H_ */
