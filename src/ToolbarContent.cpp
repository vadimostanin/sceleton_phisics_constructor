/*
 * ToolbarContent.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "ToolbarContent.h"
#include <Elementary.h>

#include <iostream>
using namespace std;

#define MAIN_EDJ "./main.edj"

ToolbarContent::ToolbarContent( Evas_Object *mainLayout ) : m_MainLayout( mainLayout )
{
	// TODO Auto-generated constructor stub
	createButtonsLayout();
	createButtonsOnButtonsLayout();

}

ToolbarContent::~ToolbarContent() {
	// TODO Auto-generated destructor stub
}

void ToolbarContent::createButtonsLayout()
{
	m_ButtonsLayout = elm_layout_add( m_MainLayout );
	elm_layout_file_set( m_ButtonsLayout, MAIN_EDJ, "group.toolbar_layout");
	evas_object_size_hint_weight_set( m_ButtonsLayout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_content_set( m_MainLayout, "part.main.toolbar", m_ButtonsLayout );
}

void on_clicked( void *data, Evas_Object *obj, void *event_info )
{
	cout << "clicked" << endl << flush;
}

void ToolbarContent::createButtonsOnButtonsLayout()
{
	Evas_Object * button = elm_button_add( m_ButtonsLayout );
	evas_object_size_hint_weight_set( button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	elm_object_part_content_set( m_ButtonsLayout, "part.toolbar_layout.button_1", button );
    elm_object_text_set( button, "Click me!");
    evas_object_smart_callback_add( button, "clicked", on_clicked, this);
	evas_object_show( button);
}
