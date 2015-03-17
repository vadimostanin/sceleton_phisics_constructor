/*
 * IGeometryObject.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef IGEOMETRYOBJECT_H_
#define IGEOMETRYOBJECT_H_

#include "GeometryObjectsTypes.h"

class IGeometryObject
{
public:
	virtual ~IGeometryObject(){}

	virtual GeometryObjectsTypes getType() = 0;

//	virtual IGeometryObject & operator = ( IGeometryObject & src ) = 0;
};


#endif /* IGEOMETRYOBJECT_H_ */
