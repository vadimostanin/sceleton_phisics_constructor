/*
 * ToolbarContentRadioParams.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentRadioParams.h"
#include <elementary-1/Elementary.h>

ToolbarContentRadioParams::ToolbarContentRadioParams( string sTitle, ToolbarItemCallback callback, void * userData ) : m_sTitle( sTitle ), m_Callback( callback ), m_UserData( userData )
{
}

ToolbarContentRadioParams::~ToolbarContentRadioParams()
{
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
	m_Callback = ((ToolbarContentRadioParams &)src).getCallback();
	m_UserData = ((ToolbarContentRadioParams &)src).getUserData();
}

ToolbarContentItemParams & ToolbarContentRadioParams::operator = ( const ToolbarContentItemParams & src )
{
	if( this == &src )
	{
		return *this;
	}

	m_Callback = ((ToolbarContentRadioParams &)src).getCallback();
	m_UserData = ((ToolbarContentRadioParams &)src).getUserData();

	return *this;
}












