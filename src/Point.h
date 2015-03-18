/*
 * Point.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef POINT_H_
#define POINT_H_

#include "IGeometryObject.h"

class Point : public IGeometryObject
{
public:
	Point();
	Point( int x, int y );
	Point( const Point & src );
	bool operator == ( const Point & src ) const;
	virtual ~Point();

	int getX() const;
	int getY() const;

	void setX( int x );
	void setY( int y );

	GeometryObjectsTypes getType();

	int getId();

	IGeometryObject * clone();

//	IGeometryObject & operator = ( IGeometryObject & src );
private:
	int m_x;
	int m_y;
	int m_Id;
};

#endif /* POINT_H_ */
