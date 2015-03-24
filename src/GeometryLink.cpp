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

GeometryObjectsTypes GeometryLink::getType()
{
	return GEOMETRYOBJECT_LINK;
}

int GeometryLink::getId()
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

void GeometryLink::setPointFrom( Point & point )
{
	m_Points[0] = point;
}

void GeometryLink::setPointTo( Point & point )
{
	m_Points[1] = point;
}

Point & GeometryLink::getPointFrom()
{
	Point & p = m_Points[0];
	return p;
}

Point & GeometryLink::getPointTo()
{
	Point & p = m_Points[1];
	return p;
}








