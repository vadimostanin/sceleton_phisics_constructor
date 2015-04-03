/*
 * GeometryLinkDynamic.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYLINKDYNAMIC_H_
#define GEOMETRYLINKDYNAMIC_H_

#include "GeometryLink.h"
#include "GeometryPointDynamic.h"
#include "IDynamicObject.h"
#include <chipmunk/chipmunk.h>

class GeometryLinkDynamic: public GeometryLink, public IDynamicObject
{
public:
	GeometryLinkDynamic( cpSpace * space );
	GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink );
	virtual ~GeometryLinkDynamic();

	void setDynamicPointFrom( GeometryPointDynamic * dynamicPoint );
	void setDynamicPointTo( GeometryPointDynamic * dynamicPoint );

	IGeometryObject & getGeometryObject();

	void update();

private:

	void initGround();

	cpSpace * m_Space;
	cpShape * m_Ground;

	GeometryPointDynamic * m_DynamicPoints[2];
};

#endif /* GEOMETRYLINKDYNAMIC_H_ */
