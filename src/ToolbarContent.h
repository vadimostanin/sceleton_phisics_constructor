/*
 * ToolbarContent.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENT_H_
#define TOOLBARCONTENT_H_

#include "ToolbarContentItem.h"
#include <Evas.h>

class ToolbarContent
{
public:
	ToolbarContent( Evas_Object *parent );
	virtual ~ToolbarContent();

	void addToolbarContentItem( ToolbarContentItem & toolbarItem );

private:
	void createButtonsLayout();

	Evas_Object * m_MainLayout;
	Evas_Object * m_ContainerBox;
	Evas_Object * m_ButtonsLayout;
};

#endif /* TOOLBARCONTENT_H_ */
