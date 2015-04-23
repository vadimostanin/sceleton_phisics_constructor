/*
 * ToolbarContentButton.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTBUTTON_H_
#define TOOLBARCONTENTBUTTON_H_

#include "ToolbarContentItem.h"
#include "ToolbarContentButtonParams.h"
#include <Evas.h>

class ToolbarContentButton : public ToolbarContentItem
{
	typedef struct
	{
		void * userData;
		ToolbarContentButton * lpThis;
	} CallbackData;

public:
	ToolbarContentButton( ToolbarContentButtonParams & params );
	virtual ~ToolbarContentButton();

	static void on_click( void *data, Evas_Object *e, void *event_info );

	void create( Evas_Object * parent );
	Evas_Object * getEvas() const;

private:

	CallbackData m_callbackData;
};

#endif /* TOOLBARCONTENTBUTTON_H_ */
