/*
 * GeometryPoint.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryPoint.h"
#include <stdlib.h>
#include <sstream>
using namespace std;

GeometryPoint::GeometryPoint() : m_x( 0 ), m_y( 0 ), m_Id( rand() )
{

}

GeometryPoint::GeometryPoint( int x, int y ) : m_x( x ), m_y( y ), m_Id( rand() )
{

}

GeometryPoint::GeometryPoint( const GeometryPoint & src ) : m_Id( rand() )
{
	m_x = src.m_x;
	m_y = src.m_y;
}

GeometryPoint & GeometryPoint::operator = ( const GeometryPoint & src )
{
	m_x = src.m_x;
	m_y = src.m_y;

	m_Id = src.m_Id;

	return *this;
}

bool GeometryPoint::operator == ( const GeometryPoint & src ) const
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

bool GeometryPoint::operator != ( const GeometryPoint & src ) const
{
	if( *this == src )
	{
		return false;
	}
	return true;
}

int GeometryPoint::getId() const
{
	return m_Id;
}

void GeometryPoint::setId( int id )
{
	m_Id = id;
}

IGeometryObject * GeometryPoint::clone()
{
	GeometryPoint * newPoint = new GeometryPoint;
	newPoint->setX( this->getX() );
	newPoint->setY( this->getY() );

	newPoint->m_Id = m_Id;

	return newPoint;
}

string GeometryPoint::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << getX() << " " << getY() << flush;

	return stream.str();
}

IGeometryObject & GeometryPoint::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_POINT )
	{
		return *this;
	}
	setX( ((GeometryPoint &)src).getX() );
	setY( ((GeometryPoint &)src).getY() );
	return *this;
}

GeometryObjectsTypes GeometryPoint::getType() const
{
	return GEOMETRYOBJECT_POINT;
}

GeometryObjectsConstructiongStates GeometryPoint::getConstructingState() const
{
	return GEOMETRYOBJECTCONSTRUCTING_COMPLETE;
}

bool GeometryPoint::isValid()
{
	return true;
}

GeometryPoint::~GeometryPoint()
{
}

int GeometryPoint::getX() const
{
	return m_x;
}

int GeometryPoint::getY() const
{
	return m_y;
}

void GeometryPoint::setX( int x )
{
	m_x = x;
}

void GeometryPoint::setY( int y )
{
	m_y = y;
}





