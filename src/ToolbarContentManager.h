/*
 * ToolbarContentManager.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTMANAGER_H_
#define TOOLBARCONTENTMANAGER_H_

#include "ToolbarContentItem.h"
#include <vector>
using namespace std;

class ToolbarContentManager
{
public:
	ToolbarContentManager();
	virtual ~ToolbarContentManager();

	void addContent( ToolbarContentItem * contentItem );

private:
	vector<ToolbarContentItem *> m_contentItems;
};

#endif /* TOOLBARCONTENTMANAGER_H_ */
