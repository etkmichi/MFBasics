/*
 * MFIInfoList.h
 *
 *  Created on: 28.12.2019
 *      Author: michl
 */

#ifndef INTERFACES_INFORMATIONS_MFIINFOLIST_H_
#define INTERFACES_INFORMATIONS_MFIINFOLIST_H_
#include <vector>
#include <cstring>
#include "../../MFData/MFDataObject.h"
class MF_I_InfoList {
private:
	std::vector<MFDataObject*>
		*mp_vecListContent,
		*mp_vecDeleteContent;

	std::string
		m_header,
		m_description;

public:
	MF_I_InfoList(std::string header);
	virtual ~MF_I_InfoList();
	void setListHeader(std::string header);
	void setListDescription(std::string Description);
	void setListContentDescription(std::vector<std::string> listContent);
	void setListContent(std::vector<MFDataObject*>* pListContent);
	std::vector<MFDataObject*>* getListContent();
	std::string getListHeader();
	std::string getListDescription();
	void addListInfo(std::string* info);
	void addListInfo(MFDataObject* info);
};

#endif /* INTERFACES_INFORMATIONS_MFIINFOLIST_H_ */
