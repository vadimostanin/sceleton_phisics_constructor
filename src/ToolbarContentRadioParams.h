/*
 * ToolbarContentRadioParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTRADIOPARAMS_H_
#define TOOLBARCONTENTRADIOPARAMS_H_

#include "ToolbarContentItemParams.h"

class ToolbarContentRadioParams: public ToolbarContentItemParams
{
public:
	ToolbarContentRadioParams( string sTitle, ToolbarItemCallback callback, void * userData );
	ToolbarContentRadioParams( const ToolbarContentRadioParams & src );
	virtual ~ToolbarContentRadioParams();

	ToolbarItemCallback getCallback() const;
	void * getUserData();
	ToolbarContentItemParams & operator = ( const ToolbarContentItemParams & src );

private:
string m_sTitle;
	ToolbarItemCallback m_Callback;
	void * m_UserData;

};

#endif /* TOOLBARCONTENTRADIOPARAMS_H_ */
