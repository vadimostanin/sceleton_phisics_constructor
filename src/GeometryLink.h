/*
 * GeometryLink.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GeometryLink_H_
#define GeometryLink_H_

#include "Point.h"
#include "IGeometryObject.h"

//typedef Point LinkPoints[2];

class GeometryLink : public IGeometryObject
{
public:
	GeometryLink();
	GeometryLink( Point & point_1, Point & point_2 );
	virtual ~GeometryLink();

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

#endif /* GeometryLink_H_ */
