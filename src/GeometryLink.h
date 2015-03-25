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

class GeometryLink : public IGeometryObject
{
public:
	GeometryLink();
	GeometryLink( Point & point_1, Point & point_2 );
	virtual ~GeometryLink();

	GeometryObjectsTypes getType() const;

	void setPointFrom( const Point & point );
	void setPointTo( const Point & point );

	const Point & getPointFrom() const;
	const Point & getPointTo() const;

	int getId() const;

	IGeometryObject * clone();
	string toString();
	bool operator == ( const GeometryLink & src );
	GeometryLink & operator = ( const GeometryLink & src );
	IGeometryObject & operator = ( IGeometryObject & src );

private:
	Point m_Points[2];
	int m_Id;
};

#endif /* GeometryLink_H_ */
