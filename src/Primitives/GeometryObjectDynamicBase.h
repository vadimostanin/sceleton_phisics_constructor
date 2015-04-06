/*
 * GeometryObjectDynamicBase.h
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#ifndef PRIMITIVES_GEOMETRYOBJECTDYNAMICBASE_H_
#define PRIMITIVES_GEOMETRYOBJECTDYNAMICBASE_H_

#include "IDynamicObject.h"

class GeometryObjectDynamicBase : public IDynamicObject
{
public:
	GeometryObjectDynamicBase();
	virtual ~GeometryObjectDynamicBase();

	virtual void update();
};

#endif /* PRIMITIVES_GEOMETRYOBJECTDYNAMICBASE_H_ */
