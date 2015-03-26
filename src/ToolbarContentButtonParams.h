/*
 * ToolbarContentButtonParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTBUTTONPARAMS_H_
#define TOOLBARCONTENTBUTTONPARAMS_H_

#include "ToolbarContentItemParams.h"
#include <string>
using namespace std;

class ToolbarContentButtonParams : public ToolbarContentItemParams
{
public:
	ToolbarContentButtonParams( string & sTitle, ToolbarItemCallback Callback, void * userData );
	ToolbarContentButtonParams( const ToolbarContentButtonParams & src );
	virtual ~ToolbarContentButtonParams();

	string getTitle() const;
	ToolbarItemCallback getCallback() const;
	void * getUserData();
	ToolbarContentItemParams & operator = ( const ToolbarContentItemParams & src );

private:

	string m_sTitle;
	ToolbarItemCallback m_Callback;
	void * m_UserData;
};

#endif /* TOOLBARCONTENTBUTTONPARAMS_H_ */
