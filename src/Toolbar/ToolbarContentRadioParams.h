/*
 * ToolbarContentRadioParams.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTRADIOPARAMS_H_
#define TOOLBARCONTENTRADIOPARAMS_H_

#include "ToolbarContentItemParams.h"
#include <Evas.h>
#include <string>
using namespace std;

class ToolbarContentRadioParams: public ToolbarContentItemParams
{
public:
	ToolbarContentRadioParams( string sTitle, ToolbarItemCallback callback, void * userData, Evas_Object * radioGroup, bool checked );
	ToolbarContentRadioParams( const ToolbarContentRadioParams & src );
	virtual ~ToolbarContentRadioParams();


	bool getChecked() const;
	Evas_Object * getRadioGroup() const;
    string getTitle() const;
	ToolbarItemCallback getCallback() const;
	void * getUserData();
	ToolbarContentItemParams & operator = ( const ToolbarContentItemParams & src );

private:

	Evas_Object * m_RadioGroup;
	string m_sTitle;
	ToolbarItemCallback m_Callback;
	void * m_UserData;
	bool m_Checked;

};

#endif /* TOOLBARCONTENTRADIOPARAMS_H_ */
