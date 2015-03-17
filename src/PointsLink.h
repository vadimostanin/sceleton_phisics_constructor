/*
 * PointsLink.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef POINTSLINK_H_
#define POINTSLINK_H_

#include "Point.h"
#include "IGeometryObject.h"

//typedef Point LinkPoints[2];

class PointsLink : public IGeometryObject
{
public:
	PointsLink();
	PointsLink( Point & point_1, Point & point_2 );
	virtual ~PointsLink();

	GeometryObjectsTypes getType();
//	IGeometryObject & operator = ( IGeometryObject & src );

	void setPointFrom( Point & point );
	void setPointTo( Point & point );

private:
	Point m_Points[2];
};

#endif /* POINTSLINK_H_ */
