/*
 * PointsLink.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "PointsLink.h"
#include <stdlib.h>

PointsLink::PointsLink() : m_Id( rand() )
{

}

PointsLink::PointsLink( Point & point_1, Point & point_2 ) : m_Id( rand() )
{
	m_Points[0] = point_1;
	m_Points[1] = point_2;
}

PointsLink::~PointsLink()
{
}

GeometryObjectsTypes PointsLink::getType()
{
	return GEOMETRYOBJECT_LINK;
}

int PointsLink::getId()
{
	return rand();
}

IGeometryObject * PointsLink::clone()
{
	PointsLink * newLink = new PointsLink;
	newLink->setPointFrom( this->getPointFrom() );
	newLink->setPointTo( this->getPointTo() );

	newLink->m_Id = m_Id;

	return newLink;
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

void PointsLink::setPointFrom( Point & point )
{
	m_Points[0] = point;
}

void PointsLink::setPointTo( Point & point )
{
	m_Points[1] = point;
}

Point & PointsLink::getPointFrom()
{
	Point & p = m_Points[0];
	return p;
}

Point & PointsLink::getPointTo()
{
	Point & p = m_Points[1];
	return p;
}








