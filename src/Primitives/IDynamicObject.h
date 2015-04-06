/*
 * IDynamicObject.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef IDynamicObject_H_
#define IDynamicObject_H_

#include "IGeometryObject.h"

class IDynamicObject
{
public:
	virtual ~IDynamicObject(){}

	virtual const IGeometryObject & getGeometryObject() const = 0;

	virtual void update() = 0;
};

#endif /* IDynamicObject_H_ */
