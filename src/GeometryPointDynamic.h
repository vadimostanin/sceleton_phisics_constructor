/*
 * GeometryPointDynamic.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYPOINTDYNAMIC_H_
#define GEOMETRYPOINTDYNAMIC_H_

#include "GeometryPoint.h"
#include "IDynamicGeometryObject.h"
#include <chipmunk/chipmunk.h>

class GeometryPointDynamic: public GeometryPoint, public IDynamicGeometryObject {
public:
	GeometryPointDynamic( cpSpace * space );
	virtual ~GeometryPointDynamic();

	void update();
private:

	void initPoint();

	cpSpace * m_Space;
	cpBody * m_BallBody;

	cpFloat m_Radius;
	cpFloat m_Mass;

};

#endif /* GEOMETRYPOINTDYNAMIC_H_ */
