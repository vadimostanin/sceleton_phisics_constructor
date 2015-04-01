/*
 * IDynamicObject.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef IDYNAMICGEOMETRYOBJECT_H_
#define IDYNAMICGEOMETRYOBJECT_H_

class IDynamicGeometryObject
{
public:
	virtual ~IDynamicGeometryObject(){}
	virtual void update() = 0;
};

#endif /* IDYNAMICGEOMETRYOBJECT_H_ */
