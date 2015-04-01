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

class GeometryPointDynamic: public GeometryPoint, public IDynamicGeometryObject {
public:
	GeometryPointDynamic();
	virtual ~GeometryPointDynamic();

	void update();
};

#endif /* GEOMETRYPOINTDYNAMIC_H_ */
