/*
 * GeometryObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFactory.h"
#include "Point.h"
#include "PointsLink.h"

GeometryObjectFactory::GeometryObjectFactory()
{

}

GeometryObjectFactory::~GeometryObjectFactory()
{
}

IGeometryObject * GeometryObjectFactory::createGeometryObject( GeometryObjectsTypes type )
{
	IGeometryObject * object = 0;
	switch( type )
	{
		case GEOMETRYOBJECT_POINT:
				object = new Point();
			break;
		case GEOMETRYOBJECT_LINK:
				object = new PointsLink();
			break;
	}
	return object;
}

GeometryObjectFactory & GeometryObjectFactory::getInstance()
{
	static GeometryObjectFactory instance;
	return instance;
}














