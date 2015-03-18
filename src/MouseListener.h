/*
 * MouseListener.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include <Evas.h>
#include "GeometryOperationTracking.h"

class MouseListener
{
public:
	MouseListener( GeometryOperationTracking &geoObjectTracker, Evas_Object *canvas );
	virtual ~MouseListener();

private:

	static void	_mouse_down(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,	void *event_info);
	static void	_mouse_move(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,	void *event_info);
	static void	_mouse_up(void *data EINA_UNUSED, Evas *e EINA_UNUSED, Evas_Object *obj,	void *event_info);

	GeometryOperationTracking & m_GeoObjectTracker;
	Evas_Object *m_Canvas;
};

#endif /* MOUSELISTENER_H_ */
