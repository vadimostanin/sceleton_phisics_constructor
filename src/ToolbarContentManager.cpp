/*
 * ToolbarContentManager.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentManager.h"

ToolbarContentManager::ToolbarContentManager()
{
}

ToolbarContentManager::~ToolbarContentManager()
{
}

void ToolbarContentManager::addContent( ToolbarContentItem * contentItem )
{
	m_contentItems.push_back( contentItem );
}
