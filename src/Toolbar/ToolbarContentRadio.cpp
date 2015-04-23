/*
 * ToolbarContentRadio.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentRadio.h"
#include <elementary-1/Elementary.h>

ToolbarContentRadio::ToolbarContentRadio( ToolbarContentRadioParams & params ) : ToolbarContentItem( TOOLBARCONTENT_RADIOBOX, params )
{
}

ToolbarContentRadio::~ToolbarContentRadio()
{
}

void ToolbarContentRadio::create( Evas_Object * parent )
{
	m_Evas = elm_radio_add( parent );
	evas_object_size_hint_align_set( m_Evas, EVAS_HINT_FILL, EVAS_HINT_FILL );
	evas_object_size_hint_weight_set( m_Evas, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND );
	string title = ((ToolbarContentRadioParams &)m_Params).getTitle();
	bool checked = ((ToolbarContentRadioParams &)m_Params).getChecked();
	elm_object_text_set( m_Evas, title.c_str() );
	elm_radio_state_value_set( m_Evas, checked == false );

	Evas_Object * radioGroup = ((ToolbarContentRadioParams &)m_Params).getRadioGroup();
	if( NULL != radioGroup )
	{
		elm_radio_group_add( m_Evas, radioGroup );
	}

	evas_object_show( m_Evas );

	evas_object_smart_callback_add( m_Evas, "changed", on_click, &m_callbackData );

	m_callbackData.lpThis = this;
	m_callbackData.userData = ((ToolbarContentRadioParams &)m_Params).getUserData();
}

Evas_Object * ToolbarContentRadio::getEvas() const
{
	return m_Evas;
}

void ToolbarContentRadio::on_click( void *data, Evas_Object *e, void *event_info )
{
	CallbackData * callbackData = (CallbackData *)data;
	ToolbarContentRadioParams & params = (ToolbarContentRadioParams &)callbackData->lpThis->m_Params;
	ToolbarItemCallback callback = params.getCallback();
	callback( callbackData->userData );
}
