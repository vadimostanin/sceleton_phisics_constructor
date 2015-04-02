/*
 * DynamicObjectFactory.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef DYNAMICOBJECTFACTORY_H_
#define DYNAMICOBJECTFACTORY_H_

#include "IDynamicObject.h"
#include "IGraphicObject.h"
#include "GeometryObjectsTypes.h"
#include <chipmunk/chipmunk.h>

class DynamicObjectFactory
{
public:
	DynamicObjectFactory();
	virtual ~DynamicObjectFactory();

	IDynamicObject * createObject( GeometryObjectsTypes type );
	IGraphicObject * createGraphicObject( IGeometryObject * geometryObject, Evas_Object * canvas );

	static DynamicObjectFactory & getInstance();

private:

	void initSpace();
	void initGround();

	cpSpace * m_Space;
	cpVect m_Gravity;
};

#endif /* DYNAMICOBJECTFACTORY_H_ */
