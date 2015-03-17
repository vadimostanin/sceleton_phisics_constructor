/*
 * GraphicsPoint.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include "GraphicPoint.h"
#include <Evas.h>

GraphicPoint::GraphicPoint() : m_Evas( 0 )
{
}

GraphicPoint::~GraphicPoint()
{
	evas_object_del( getEvas() );
}

GraphicPoint::GraphicPoint( const Point & point ) : m_Point( point ), m_Evas( 0 )
{
}

GraphicPoint::GraphicPoint( int x, int y )
{
	m_Point.setX( x );
	m_Point.setY( y );
	m_Evas = 0;
}

GraphicPoint::GraphicPoint( const GraphicPoint & src )
{
	m_Point = src.m_Point;
	m_Evas = src.m_Evas;
}

bool GraphicPoint::operator ==( const GraphicPoint & src )
{
	if( m_Point == src.m_Point )
	{
		return true;
	}
	return false;
}

int GraphicPoint::getX()
{
	return m_Point.getX();
}

int GraphicPoint::getY()
{
	return m_Point.getY();
}

void GraphicPoint::setX( int x )
{
	m_Point.setX( x );
}

void GraphicPoint::setY( int y )
{
	m_Point.setY( y );
}

Evas_Object * GraphicPoint::getEvas() const
{
	return m_Evas;
}

void GraphicPoint::setEvas( Evas_Object * evas )
{
	m_Evas = evas;
}

void GraphicPoint::draw( Evas * canvas )
{
	const int rect_width = 10;
	const int rect_height = 10;

	Evas_Object *r1 = evas_object_rectangle_add( canvas );

	evas_object_move( r1, getX() - rect_width/2, getY() - rect_height / 2 );

	evas_object_color_set(r1, 0, 0, 255, 255);

	evas_object_propagate_events_set( r1, EINA_TRUE );

	evas_object_resize(r1, rect_width, rect_height);
	evas_object_show(r1);

	setEvas( r1 );
}








