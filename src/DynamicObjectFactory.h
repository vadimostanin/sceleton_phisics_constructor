/*
 * DynamicObjectFactory.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICOBJECTFACTORY_H_
#define DYNAMICOBJECTFACTORY_H_

#include "IDynamicGeometryObject.h"
#include "GeometryObjectsTypes.h"
#include <chipmunk/chipmunk.h>

class DynamicObjectFactory
{
public:
	DynamicObjectFactory();
	virtual ~DynamicObjectFactory();

	IDynamicGeometryObject * createObject( GeometryObjectsTypes type );

	static DynamicObjectFactory & getInstance();

private:

	void initSpace();
	void initGround();

	cpSpace * m_Space;
	cpVect m_Gravity;
};

#endif /* DYNAMICOBJECTFACTORY_H_ */
