/*
 * GeometryPointDynamic.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYPOINTDYNAMIC_H_
#define GEOMETRYPOINTDYNAMIC_H_

#include "GeometryPoint.h"
#include "IDynamicObject.h"
#include <chipmunk/chipmunk.h>

class GeometryPointDynamic: virtual public GeometryPoint, public IDynamicObject
{
public:
	GeometryPointDynamic( cpSpace * space );
	GeometryPointDynamic( cpSpace * space, GeometryPoint * geometryPoint );
	virtual ~GeometryPointDynamic();

	cpFloat getRadius() const;
	cpFloat getMass()   const;

	cpBody * getBody() const;
	cpShape * getShape() const;
	cpSpace * getSpace() const;

	const IGeometryObject & getGeometryObject() const;

	void update();
private:

	void initPoint();

	cpSpace 	 * m_Space;
	cpBody  	 * m_BallBody;
	cpShape 	 * m_BallShape;
	cpConstraint * m_IntermidiateConstraint;
	cpBody  	 * m_OuterBody;

	cpFloat m_Radius;
	cpFloat m_Mass;

};

#endif /* GEOMETRYPOINTDYNAMIC_H_ */
