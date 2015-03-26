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
	GeometryLink( GeometryPoint & point_1, GeometryPoint & point_2 );
	virtual ~GeometryLink();

	GeometryObjectsTypes getType() const;

	void setPointFrom( const GeometryPoint & point );
	void setPointTo( const GeometryPoint & point );

	const GeometryPoint & getPointFrom() const;
	const GeometryPoint & getPointTo() const;

	int getId() const;

	IGeometryObject * clone();
	string toString();
	bool operator == ( const GeometryLink & src );
	GeometryLink & operator = ( const GeometryLink & src );
	IGeometryObject & operator = ( IGeometryObject & src );

private:
	GeometryPoint m_Points[2];
	int m_Id;
};

#endif /* GeometryLink_H_ */
