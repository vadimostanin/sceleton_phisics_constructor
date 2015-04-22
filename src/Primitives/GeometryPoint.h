/*
 * GeometryPoint.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef POINT_H_
#define POINT_H_

#include "IGeometryObject.h"

class GeometryPoint : public IGeometryObject
{
public:
	GeometryPoint();
	GeometryPoint( int x, int y );
	GeometryPoint( const GeometryPoint & src );
	bool operator == ( const GeometryPoint & src ) const;
	bool operator != ( const GeometryPoint & src ) const;
	GeometryPoint & operator = ( const GeometryPoint & src );
	~GeometryPoint();

	int getX() const;
	int getY() const;

	void setX( int x );
	void setY( int y );

	GeometryObjectsTypes getType() const;
	GeometryObjectsConstructiongStates getConstructingState() const;
	int getId() const;
	void setId( int id );
	IGeometryObject * clone();
	string toString();
	bool isValid();
	IGeometryObject & operator = ( IGeometryObject & src );

private:
	int m_x;
	int m_y;
	int m_Id;
};

#endif /* POINT_H_ */
