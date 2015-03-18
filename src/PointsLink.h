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

	Point & getPointFrom();
	Point & getPointTo();

	int getId();

	IGeometryObject * clone();

private:
	Point m_Points[2];
	int m_Id;
};

#endif /* POINTSLINK_H_ */
