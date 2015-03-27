/*
 * MouseListener.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "MouseListener.h"
#include <iostream>
using namespace std;

MouseListener::MouseListener( IGeometryObjectTracker * geoObjectTracker, Evas_Object *canvas ) :
		m_Tracker( geoObjectTracker ), m_Canvas( canvas )
{
	evas_object_event_callback_add( m_Canvas, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down, this);
	evas_object_event_callback_add( m_Canvas, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move, this);
	evas_object_event_callback_add( m_Canvas, EVAS_CALLBACK_MOUSE_UP, _mouse_up, this);
}

MouseListener::~MouseListener()
{
}

IGeometryObjectTracker * MouseListener::getMouseTracker() const
{
	return m_Tracker;
}

void MouseListener::setMouseTracker( IGeometryObjectTracker * tracker )
{
	m_Tracker = tracker;
}

void MouseListener::_mouse_down(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Down *mdInfo = (Evas_Event_Mouse_Down *)event_info;

	MouseListener * lpThis = (MouseListener *)data;

	if( NULL == lpThis->m_Tracker )
	{
		return;
	}

	int x = mdInfo->output.x;
	int y = mdInfo->output.y;

//	cout << "mouse down x=" << x << "; y=" << y << endl << flush;

	if( mdInfo->button == 1 )
	{
		lpThis->m_Tracker->trackerBegin( x, y );
	}
	else if( mdInfo->button == 3 )
	{
		lpThis->m_Tracker->deleteObject( x, y );
	}
}

void MouseListener::_mouse_move(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Move *mmInfo = (Evas_Event_Mouse_Move *)event_info;

	MouseListener * lpThis = (MouseListener *)data;

	if( NULL == lpThis->m_Tracker )
	{
		return;
	}

	int x = mmInfo->cur.output.x;
	int y = mmInfo->cur.output.y;

	lpThis->m_Tracker->trackerContinue( x, y );

//	cout << "mouse move x=" << mmInfo->cur.output.x << "; y=" << mmInfo->cur.output.y << endl << flush;
}

void MouseListener::_mouse_up(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj, void *event_info)
{
	Evas_Event_Mouse_Up *muInfo = (Evas_Event_Mouse_Up *)event_info;

	MouseListener * lpThis = (MouseListener *)data;

	if( NULL == lpThis->m_Tracker )
	{
		return;
	}

	int x = muInfo->output.x;
	int y = muInfo->output.y;

//	cout << "mouse up x=" << x << "; y=" << y << endl << flush;

	lpThis->m_Tracker->trackerEnd( x, y );
}
