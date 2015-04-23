/*
 * ToolbarContentRadio.h
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#ifndef TOOLBARCONTENTRADIO_H_
#define TOOLBARCONTENTRADIO_H_

#include "ToolbarContentItem.h"
#include "ToolbarContentRadioParams.h"

class ToolbarContentRadio: public ToolbarContentItem
{
	typedef struct
	{
		void * userData;
		ToolbarContentRadio * lpThis;
	} CallbackData;

public:
	ToolbarContentRadio( ToolbarContentRadioParams & params );
	virtual ~ToolbarContentRadio();

	static void on_click( void *data, Evas_Object *e, void *event_info );

	void create( Evas_Object * parent );
	Evas_Object * getEvas() const;

private:

	CallbackData m_callbackData;

};

#endif /* TOOLBARCONTENTRADIO_H_ */
