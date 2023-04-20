/*
 * MFStructurableDataSetup.h
 *
 *  Created on: 24.03.2020
 *      Author: michl
 */

#ifndef MFDATA_MFSTRUCTURABLEDATASETUP_H_
#define MFDATA_MFSTRUCTURABLEDATASETUP_H_

#include "MFStructurableData.h"
#include "../MFObjects/MFObject.h"

/**
 * This class can be used for loading/storing/strucuring setups. If a specific class
 * depends on a setup, it can extend this class. To create setup related data, the
 * initData() and setupDataStructure() must be implemented.
 * The initData() is used
 * in a constructor or during initialization and should initialize data which is needed
 * by the setupDataStructure().
 * The setupDataStructure() should use functionality of MFStructurableData (add...Data
 * functions) to add custom setup structure.
 * F.e. a index (uint32_t) to a table must be stored. Add addData(uint32_t* data) to
 * the setupDataStructure() function like "addData(&m_taskIndex);".
 */
class MFStructurableDataSetup :
		public MFStructurableData {
private:
	std::string
		m_name;
public:
	/**
	 * This function inits (creates/allocates) all setup related data, which is
	 * needed for the setupDataStructure() call.
	 */
	virtual void initData(){
		MFObject::printWarning("MFStructurableDataSetup debug - no initData");
	};

	/**
	 * This function adds all setup related data to this MFStructurableData
	 */
	virtual void setupDataStructure(){
		MFObject::printWarning("MFStructurableDataSetup debug - no data structure setup");
	};

	/**
	 * Sets up the object from the setup structure and data of this object. The object's
	 * setup must be loaded/initialized before a call to this function is valid.
	 * Object setup depends on the object class.
	 * @return
	 */
	virtual bool loadFromSetup(){
		MFObject::printErr("MFStructurableDataSetup::loadFromSetup - not implemented!"
				" Implementation is subclass specific!");
		return false;
	}

	/**
	 * Updates the object from its setup structure and data. The object's
	 * setup must be loaded/initialized before a call to this function is valid.
	 * After a change of structure or data this update function may update an object's
	 * private fields.
	 * Object setup depends on the object class.
	 * @return
	 */
	virtual bool updateData(){
		MFObject::printErr("MFStructurableDataSetup::updateData - not implemented!"
				" Implementation is subclass specific!");
		return false;
	}

	/**
	 * Implementaiton of this function shall init the subclass by the given setup.
	 * @param pData if no setup was loaded, this parameter can be used to give a setup for
	 * loading.
	 * @return
	 */
	virtual bool initFromSetup(MFStructurableDataSetup* pData=nullptr){
		MFObject::printErr("bool MFStructurableDataSetup::initFromSetup - not implemented!");
		return false;
	}

	/**
	 *
	 * @param pData
	 * @return
	 */
	virtual bool initFromData(MFDataObject* pData){
		MFObject::printErr("bool MFStructurableDataSetup::initFromData - not implemented!");
		return false;
	};
public:
	MFStructurableDataSetup();
	virtual ~MFStructurableDataSetup();

	static void setSetupPath(std::string path){};
	/**
	 * Loads the setup from static setup path
	 * @return
	 */
	bool loadSetup(){
		MFObject::printErr("MFStructurableDataSetup::loadSetup - "
				"This function is not virtual and has no implementation (TODO)");
		return false;
	};

	/**
	 * Clears the current setup and loads the setup from the given structurable data.
	 * @param pdata
	 * @return false if data structure doesn't match this objects data structure.
	 */
	bool loadSetup(MFStructurableData* pdata);
	void saveSetup(){
		MFObject::printErr("MFStructurableDataSetup::saveSetup - no impl.!");};
	void saveDataToDatabase(std::string table,std::string databaseFile);
	void setSetupName(std::string name){m_name=name;};
	std::string getSetupName(){return m_name;};
};

#endif /* MFDATA_MFSTRUCTURABLEDATASETUP_H_ */
