/*
 * IDynamicObject.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef IDynamicObject_H_
#define IDynamicObject_H_

#include "IObject.h"
#include "IGeometryObject.h"

class IDynamicObject : public IObject
{
public:
	virtual ~IDynamicObject(){}
	virtual void update() = 0;
};

#endif /* IDynamicObject_H_ */
