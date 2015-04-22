/*
 * GeometryLink.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GeometryLink_H_
#define GeometryLink_H_

#include "GeometryPoint.h"
#include "IGeometryObject.h"

class GeometryLink : public IGeometryObject
{
public:
	GeometryLink();
	GeometryLink( GeometryPoint * point_1, GeometryPoint * point_2 );
	virtual ~GeometryLink();

	bool operator == ( const GeometryLink & src ) const;
	bool operator != ( const GeometryLink & src ) const;
	GeometryLink & operator = ( const GeometryLink & src );

	void setPointFrom( const GeometryPoint * point );
	void setPointTo( const GeometryPoint * point );

	const GeometryPoint * getPointFrom() const;
	const GeometryPoint * getPointTo() const;

	int getMiddleX() const;
	int getMiddleY() const;

	int getId() const;
	void setId( int id );
	GeometryObjectsTypes getType() const;
	GeometryObjectsConstructiongStates getConstructingState() const;
	IGeometryObject * clone();
	string toString();
	IGeometryObject & operator = ( IGeometryObject & src );
	bool isValid();

	int getWidth() const;

private:
	const GeometryPoint * m_Points[2];
	int m_Id;
};

#endif /* GeometryLink_H_ */
