/*
 * ToolbarContentItem.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentItem.h"

ToolbarContentItem::ToolbarContentItem( ToolbarContentTypes type, ToolbarContentItemParams & params ) : m_Type( type ), m_Params( params ), m_Evas( 0 )
{
}

ToolbarContentItem::~ToolbarContentItem()
{
}

