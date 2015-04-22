/*
 * GeometryDummy.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYDUMMY_H_
#define GEOMETRYDUMMY_H_

#include "IGeometryObject.h"

class GeometryDummy: public IGeometryObject
{
public:
	GeometryDummy();
	GeometryDummy( const GeometryDummy & src );
	virtual ~GeometryDummy();

	GeometryObjectsTypes getType() const;
	GeometryObjectsConstructiongStates getConstructingState() const;
	int getId() const;
	void setId( int id);
	IGeometryObject * clone();
	string toString();
	bool isValid();
	IGeometryObject & operator = ( IGeometryObject & src );

private:
	int m_Id;
};

#endif /* GEOMETRYDUMMY_H_ */
