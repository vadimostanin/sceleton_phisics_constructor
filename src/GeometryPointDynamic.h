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

class GeometryPointDynamic: virtual public GeometryPoint, public IDynamicObject {
public:
//	GeometryPointDynamic();
	GeometryPointDynamic( cpSpace * space );
	virtual ~GeometryPointDynamic();

	IGeometryObject * clone();
	bool isValid();
	string toString();
	int getId() const;
	GeometryObjectsTypes getType() const;
	IGeometryObject & operator = ( IGeometryObject & src );
	void update();
private:

	void initPoint();

	cpSpace * m_Space;
	cpBody * m_BallBody;

	cpFloat m_Radius;
	cpFloat m_Mass;

};

#endif /* GEOMETRYPOINTDYNAMIC_H_ */
