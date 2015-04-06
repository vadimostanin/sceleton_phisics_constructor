/*
 * ToolbarContentItem.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTITEM_H_
#define TOOLBARCONTENTITEM_H_

#include "ToolbarContentTypes.h"
#include "ToolbarContentItemParams.h"
#include <Evas.h>

class ToolbarContentItem
{
public:

	ToolbarContentItem( ToolbarContentTypes type, ToolbarContentItemParams & params );
	virtual ~ToolbarContentItem();

	virtual void create( Evas_Object * parent ) = 0;
	virtual Evas_Object * getEvas() const = 0;

	ToolbarContentTypes m_Type;
	ToolbarContentItemParams & m_Params;
	Evas_Object * m_Evas;
};

#endif /* TOOLBARCONTENTITEM_H_ */
