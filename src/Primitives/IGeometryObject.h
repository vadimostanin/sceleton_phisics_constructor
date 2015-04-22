/*
 * IGeometryObject.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef IGEOMETRYOBJECT_H_
#define IGEOMETRYOBJECT_H_

#include "GeometryObjectsTypes.h"
#include "GeometryObjectsConstructiongStates.h"
#include <string>
using namespace std;

class IGeometryObject
{
public:
	virtual ~IGeometryObject(){}

	virtual GeometryObjectsTypes getType() const = 0;
	virtual GeometryObjectsConstructiongStates getConstructingState() const = 0;
	virtual int getId() const = 0;
	virtual IGeometryObject * clone() = 0;
	virtual string toString() = 0;
    virtual bool isValid() = 0;

	virtual IGeometryObject & operator = ( IGeometryObject & src ) = 0;
};


#endif /* IGEOMETRYOBJECT_H_ */
