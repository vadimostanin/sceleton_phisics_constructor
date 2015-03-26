/*
 * ToolbarContentButtonParams.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "ToolbarContentButtonParams.h"

ToolbarContentButtonParams::ToolbarContentButtonParams( string & sTitle, ToolbarItemCallback Callback, void * userData ) : m_sTitle( sTitle ), m_Callback( Callback ), m_UserData( userData )
{
}

ToolbarContentButtonParams::~ToolbarContentButtonParams()
{
}

string ToolbarContentButtonParams::getTitle() const
{
	return m_sTitle;
}

ToolbarItemCallback ToolbarContentButtonParams::getCallback() const
{
	return m_Callback;
}

void * ToolbarContentButtonParams::getUserData()
{
	return m_UserData;
}

ToolbarContentButtonParams::ToolbarContentButtonParams( const ToolbarContentButtonParams & src )
{
	m_sTitle = ((ToolbarContentButtonParams &)src).getTitle();
	m_Callback = ((ToolbarContentButtonParams &)src).getCallback();
	m_UserData = ((ToolbarContentButtonParams &)src).getUserData();
}

ToolbarContentItemParams & ToolbarContentButtonParams::operator = ( const ToolbarContentItemParams & src )
{
	if( this == &src )
	{
		return *this;
	}

	m_sTitle = ((ToolbarContentButtonParams &)src).getTitle();
	m_Callback = ((ToolbarContentButtonParams &)src).getCallback();

	return *this;
}














