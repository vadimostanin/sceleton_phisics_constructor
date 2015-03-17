/*
 * GraphicPointHighlighted.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPointHighlighted.h"

GraphicPointHighlighted::GraphicPointHighlighted()
{
}

GraphicPointHighlighted::~GraphicPointHighlighted()
{
}

GraphicPointHighlighted::GraphicPointHighlighted( int x, int y )
{
	;
}

GraphicPointHighlighted::GraphicPointHighlighted( const Point & point )
{
	;
}

GraphicPointHighlighted::GraphicPointHighlighted( const GraphicPoint & src )
{
	;
}

void GraphicPointHighlighted::draw( Evas * canvas )
{
	const int rect_width = 10;
	const int rect_height = 10;

	Evas_Object *r1 = evas_object_rectangle_add( canvas );

	evas_object_move( r1, getX() - rect_width/2, getY() - rect_height / 2 );

	evas_object_color_set(r1, 0, 255, 0, 255);

	evas_object_propagate_events_set( r1, EINA_TRUE );

	evas_object_resize(r1, rect_width, rect_height);
	evas_object_show(r1);

	setEvas( r1 );
}










