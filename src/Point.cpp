/*
 * Point.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "Point.h"

Point::Point() : m_x( 0 ), m_y( 0 )
{

}

Point::Point( int x, int y ) : m_x( x ), m_y( y )
{

}

Point::Point( const Point & src )
{
	m_x = src.m_x;
	m_y = src.m_y;
}

bool Point::operator==( const Point & src )
{
	if( getX() != src.getX() )
	{
		return false;
	}
	if( getY() != src.getY() )
	{
		return false;
	}
	return true;
}

//IGeometryObject & Point::operator = ( IGeometryObject & src )
//{
//	if( src.getType() != GEOMETRYOBJECT_POINT )
//	{
//		return *this;
//	}
//	setX( ((Point)src).getX() );
//	setY( ((Point)src).getY() );
//	return this;
//}

Point::~Point()
{
}

int Point::getX() const
{
	return m_x;
}

int Point::getY() const
{
	return m_y;
}

void Point::setX( int x )
{
	m_x = x;
}

void Point::setY( int y )
{
	m_y = y;
}

GeometryObjectsTypes Point::getType()
{
	return GEOMETRYOBJECT_POINT;
}


