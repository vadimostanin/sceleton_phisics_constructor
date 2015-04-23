/*
 * ToolbarContent.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "ToolbarContent.h"
#include "ToolbarContentButton.h"
#include <Elementary.h>

#include <iostream>
using namespace std;

//#define MAIN_EDJ "/opt/usr/apps/org.tizen.tizen_porting/res/edje/main.edj"
#define MAIN_EDJ "./main.edj"

void on_button_click( void * user_data )
{
	cout << "on_button_click" << endl << flush;
}

ToolbarContent::ToolbarContent( Evas_Object *mainLayout ) : m_MainLayout( mainLayout )
{
	createButtonsLayout();
}

ToolbarContent::~ToolbarContent()
{
}

void ToolbarContent::createButtonsLayout()
{
	m_ButtonsLayout = elm_layout_add( m_MainLayout );
	elm_layout_file_set( m_ButtonsLayout, MAIN_EDJ, "group.toolbar_layout");
	evas_object_size_hint_weight_set( m_ButtonsLayout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set( m_MainLayout, "part.main.toolbar", m_ButtonsLayout );

	m_ContainerBox = elm_box_add( m_ButtonsLayout );
	evas_object_size_hint_align_set( m_ContainerBox, EVAS_HINT_FILL, EVAS_HINT_FILL );
	evas_object_size_hint_weight_set( m_ContainerBox, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	elm_box_horizontal_set( m_ContainerBox, EINA_TRUE );
	elm_object_part_content_set( m_ButtonsLayout, "part.toolbar_layout.main_box", m_ContainerBox );
//	m_ContainerBox = elm_object_part_content_get( m_ButtonsLayout, "part.toolbar_layout.main_box" );//Work
	evas_object_show( m_ContainerBox );
}

void ToolbarContent::addToolbarContentItem( ToolbarContentItem & toolbarItem )
{
	toolbarItem.create( m_ContainerBox );

	Evas_Object * button = toolbarItem.getEvas();
	elm_box_pack_end( m_ContainerBox, button );
	evas_object_show( m_ContainerBox );
}













