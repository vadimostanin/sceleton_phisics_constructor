/*
 * GeometryObjectFactory.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTFACTORY_H_
#define GEOMETRYOBJECTFACTORY_H_

#include "IGeometryObject.h"
#include "IGraphicObject.h"
#include "GeometryObjectsTypes.h"

class GeometryObjectFactory
{
public:
	GeometryObjectFactory();
	virtual ~GeometryObjectFactory();

	IGeometryObject * createGeometryObject( GeometryObjectsTypes type );
	IGraphicObject * createGraphicObject( IGeometryObject * geometryObject, Evas_Object * canvas );

	static GeometryObjectFactory & getInstance();
};

#endif /* GEOMETRYOBJECTFACTORY_H_ */
