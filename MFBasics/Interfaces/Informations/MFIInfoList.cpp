/*
 * MFIInfoList.cpp
 *
 *  Created on: 28.12.2019
 *      Author: michl
 */

#include "MFIInfoList.h"

MF_I_InfoList::MF_I_InfoList(std::string header) {
	mp_vecListContent = new std::vector<MFDataObject*>();
	mp_vecDeleteContent = new std::vector<MFDataObject*>();
	m_header=header;
	m_description="";
}

MF_I_InfoList::~MF_I_InfoList() {
	for(MFDataObject* pO:*mp_vecDeleteContent){
		delete pO;
		pO=nullptr;
	}
	delete mp_vecListContent;
	delete mp_vecDeleteContent;
}

void MF_I_InfoList::setListHeader(std::string header){
	m_header=header;
}

void MF_I_InfoList::setListDescription(std::string Description){
	m_description=Description;
}

void MF_I_InfoList::setListContentDescription(std::vector<std::string> listContent){

}

void MF_I_InfoList::setListContent(std::vector<MFDataObject*>* pListContent){
	mp_vecListContent=pListContent;
}

std::vector<MFDataObject*>* MF_I_InfoList::getListContent(){
	return mp_vecListContent;
}

std::string MF_I_InfoList::getListHeader(){
	return m_header;
}

std::string MF_I_InfoList::getListDescription(){
	return m_description;
}

void MF_I_InfoList::addListInfo(std::string* info){
	MFDataObject* pDataObject=new MFDataObject();
	pDataObject->setDataType(E_DataType::DATA_TYPE_STRING);
	pDataObject->setDataByteSize(sizeof(char)*info->length());
	pDataObject->setData(info);
	pDataObject->setGuiType(E_GuiElement::GUI_TYPE_TEXT_VIEW);
	mp_vecListContent->push_back(pDataObject);
	mp_vecDeleteContent->push_back(pDataObject);
}

void MF_I_InfoList::addListInfo(MFDataObject *info){

}

