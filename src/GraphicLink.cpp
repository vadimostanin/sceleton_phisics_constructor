/*
 * GraphicLink.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: vostanin
 */

#include <iostream>

#include "GraphicLink.h"
using namespace std;

GraphicLink::GraphicLink() : m_Evas( 0 )
{

}

GraphicLink::GraphicLink( const GraphicLink & src )
{
	setEvas( src.getEvas() );
}

//GraphicLink::GraphicLink( const PointsLink src ) : m_Evas( 0 )
//{
//	setPointFrom( src.getPointFrom() );
//	setPointTo( src.getPointTo() );
//}

GraphicLink & GraphicLink::operator = ( PointsLink & src )
{
	setPointFrom( src.getPointFrom() );
	setPointTo( src.getPointTo() );

	return *this;
}

GraphicLink::~GraphicLink()
{
//	evas_object_del( getEvas() );
}

void GraphicLink::draw( Evas * canvas )
{
//	setEvas( evas_object_line_add( canvas ) );
//
//	evas_object_line_xy_set( getEvas(), getPointFrom().getX(), getPointFrom().getY(), getPointTo().getX(), getPointTo().getY() );
//
//	evas_object_color_set( getEvas(), 0, 0, 0, 255 );

	cout << "draw link from:" << getPointFrom().getX() << "x" << getPointFrom().getY() << "; to:" <<
						getPointTo().getX() << "x" << getPointTo().getY() << endl << flush;

//	evas_object_show( getEvas() );
}

Evas_Object * GraphicLink::getEvas() const
{
	return m_Evas;
}

void GraphicLink::setEvas( Evas_Object * evas )
{
	m_Evas = evas;
}

void GraphicLink::setPointFrom( Point & point )
{
	m_Points[0] = point;
}

void GraphicLink::setPointTo( Point & point )
{
	m_Points[1] = point;
}

Point & GraphicLink::getPointFrom()
{
	return m_Points[0];
}

Point & GraphicLink::getPointTo()
{
	return m_Points[1];
}
















