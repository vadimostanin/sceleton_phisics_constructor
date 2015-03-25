/*
 * GeometryLink.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryLink.h"
#include <stdlib.h>
#include <sstream>
using namespace std;

GeometryLink::GeometryLink() : m_Id( rand() )
{

}

GeometryLink::GeometryLink( Point & point_1, Point & point_2 ) : m_Id( rand() )
{
	m_Points[0] = point_1;
	m_Points[1] = point_2;
}

GeometryLink::~GeometryLink()
{
}

GeometryObjectsTypes GeometryLink::getType() const
{
	return GEOMETRYOBJECT_LINK;
}

int GeometryLink::getId() const
{
	return rand();
}

IGeometryObject * GeometryLink::clone()
{
	GeometryLink * newLink = new GeometryLink;
	newLink->setPointFrom( this->getPointFrom() );
	newLink->setPointTo( this->getPointTo() );

	newLink->m_Id = m_Id;

	return newLink;
}

string GeometryLink::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << getPointFrom().getId() << " " << getPointTo().getId() << flush;

	return stream.str();
}

GeometryLink & GeometryLink::operator = ( const GeometryLink & src )
{
	if( *this == src )
	{
		return *this;
	}
	const Point & point = src.getPointFrom();
	setPointFrom( point );
	setPointTo( src.getPointTo() );
	return *this;
}

bool GeometryLink::operator == ( const GeometryLink & src )
{
	if( getPointFrom() != src.getPointFrom() )
	{
		return false;
	}
	if( getPointTo() !=  src.getPointTo() )
	{
		return false;
	}
	return true;
}

IGeometryObject & GeometryLink::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_LINK )
	{
		return *this;
	}
	setPointFrom( ((GeometryLink &)src).getPointFrom() );
	setPointTo(   ((GeometryLink &)src).getPointTo()   );
	return *this;
}

void GeometryLink::setPointFrom( const Point & point )
{
	m_Points[0] = point;
}

void GeometryLink::setPointTo( const Point & point )
{
	m_Points[1] = point;
}

const Point & GeometryLink::getPointFrom() const
{
	const Point & p = m_Points[0];
	return p;
}

const Point & GeometryLink::getPointTo() const
{
	const Point & p = m_Points[1];
	return p;
}








