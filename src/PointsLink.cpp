/*
 * PointsLink.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "PointsLink.h"

PointsLink::PointsLink()
{

}

PointsLink::PointsLink( Point & point_1, Point & point_2 )
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










