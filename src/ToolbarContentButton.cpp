/*
 * ToolbarContentButton.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentButton.h"
#include "ToolbarContentTypes.h"
#include <elementary-1/Elementary.h>

ToolbarContentButton::ToolbarContentButton( ToolbarContentButtonParams & params ) : ToolbarContentItem( TOOLBARCONTENT_BUTTON, params ), m_Evas( 0 )
{
}

ToolbarContentButton::~ToolbarContentButton()
{
	evas_object_del( m_Evas );
}

void ToolbarContentButton::create( Evas_Object * parent )
{
	m_Evas = elm_button_add( parent );
	evas_object_size_hint_align_set( m_Evas, EVAS_HINT_FILL, EVAS_HINT_FILL );
	evas_object_size_hint_weight_set( m_Evas, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	evas_object_show( m_Evas );

	evas_object_smart_callback_add( m_Evas, "clicked", on_click, &m_callbackData );


	m_callbackData.lpThis = this;
	m_callbackData.userData = ((ToolbarContentButtonParams &)m_Params).getUserData();
}

Evas_Object * ToolbarContentButton::getEvas() const
{
	return m_Evas;
}

void ToolbarContentButton::on_click( void *data, Evas *e, void *event_info )
{
	CallbackData * callbackData = (CallbackData *)data;
	ToolbarContentButtonParams & params = (ToolbarContentButtonParams &)callbackData->lpThis->m_Params;
	ToolbarItemCallback callback = params.getCallback();
	callback( callbackData->userData );
}
















