/*
 * ToolbarContentRadioParams.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentRadioParams.h"
#include <elementary-1/Elementary.h>

ToolbarContentRadioParams::ToolbarContentRadioParams( string sTitle, ToolbarItemCallback callback, void * userData, Evas_Object * radioGroup, bool checked ) :
				m_RadioGroup( radioGroup ), m_sTitle( sTitle ), m_Callback( callback ), m_UserData( userData ), m_Checked( checked )
{
}

ToolbarContentRadioParams::~ToolbarContentRadioParams()
{
}

bool ToolbarContentRadioParams::getChecked() const
{
	return m_Checked;
}

Evas_Object * ToolbarContentRadioParams::getRadioGroup() const
{
	return m_RadioGroup;
}

string ToolbarContentRadioParams::getTitle() const
{
    return m_sTitle;
}

ToolbarItemCallback ToolbarContentRadioParams::getCallback() const
{
	return m_Callback;
}

void * ToolbarContentRadioParams::getUserData()
{
	return m_UserData;
}

ToolbarContentRadioParams::ToolbarContentRadioParams( const ToolbarContentRadioParams & src )
{
	m_Checked = ((ToolbarContentRadioParams &)src).getChecked();
	m_RadioGroup = ((ToolbarContentRadioParams &)src).getRadioGroup();
	m_Callback = ((ToolbarContentRadioParams &)src).getCallback();
	m_UserData = ((ToolbarContentRadioParams &)src).getUserData();
}

ToolbarContentItemParams & ToolbarContentRadioParams::operator = ( const ToolbarContentItemParams & src )
{
	if( this == &src )
	{
		return *this;
	}

	m_RadioGroup = ((ToolbarContentRadioParams &)src).getRadioGroup();
	m_Callback = ((ToolbarContentRadioParams &)src).getCallback();
	m_UserData = ((ToolbarContentRadioParams &)src).getUserData();

	return *this;
}












