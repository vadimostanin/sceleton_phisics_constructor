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
#include <EPhysics.h>

class GeometryPointDynamic: virtual public GeometryPoint, public IDynamicObject
{
public:
	GeometryPointDynamic( cpSpace * space, GeometryPoint * geometryPoint );
	GeometryPointDynamic( EPhysics_World * world, GeometryPoint * geometryPoint );
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
	void initEphysicsPoint();

	cpSpace 	 * m_Space;
	cpBody  	 * m_BallBody;
	cpShape 	 * m_BallShape;

	cpFloat m_Radius;
	cpFloat m_Mass;

	EPhysics_World * m_Ephysics_World;
	EPhysics_Body  * m_Ephysics_Body;

};

#endif /* GEOMETRYPOINTDYNAMIC_H_ */
