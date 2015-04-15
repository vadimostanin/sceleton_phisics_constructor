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

	cpBody * getBody() const;
	cpShape * getShape() const;
	cpSpace * getSpace() const;

	const GeometryPointDynamic * getDynamicPointFrom() const;
	const GeometryPointDynamic * getDynamicPointTo() const;

	const IGeometryObject & getGeometryObject() const;

	void update();

private:

	void initLink();
	void initJoints();
	void clearJoints();

	cpSpace * m_Space;
	cpBody  * m_Body;
	cpShape * m_Shape;

	cpConstraint * m_ConstraintFrom;
	cpConstraint * m_ConstraintTo;


	GeometryPointDynamic * m_DynamicPoints[2];
};

#endif /* GEOMETRYLINKDYNAMIC_H_ */
