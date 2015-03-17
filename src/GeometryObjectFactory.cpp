/*
 * GeometryObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFactory.h"
#include "Point.h"
#include "PointsLink.h"
#include "GraphicPoint.h"
#include "GraphicPointHighlighted.h"
#include "GraphicPointLink.h"

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
		case GEOMETRYOBJECT_POINT_HIGHLIGHTED:
				object = new Point();
			break;
		case GEOMETRYOBJECT_LINK:
				object = new PointsLink();
			break;
	}
	return object;
}

IGraphicObject * GeometryObjectFactory::createGraphicObject( GeometryObjectsTypes type )
{
	IGraphicObject * object = 0;
	switch( type )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GraphicPoint();
			break;
		case GEOMETRYOBJECT_POINT_HIGHLIGHTED:
				object = new GraphicPointHighlighted();
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GraphicPointLink();
			break;
	}
	return object;
}

GeometryObjectFactory & GeometryObjectFactory::getInstance()
{
	static GeometryObjectFactory instance;
	return instance;
}














