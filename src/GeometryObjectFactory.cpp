/*
 * GeometryObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFactory.h"

#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GeometrySpring.h"
#include "GraphicPoint.h"
#include "GraphicPointHighlighted.h"
#include "GraphicLink.h"

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
				object = new GeometryPoint();
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GeometryLink();
			break;
		case GEOMETRYOBJECT_SPRING:
				object = new GeometrySpring();
			break;
	}
	return object;
}

IGraphicObject * GeometryObjectFactory::createGraphicObject( IGeometryObject * geometryObject, Evas_Object * canvas )
{
	IGraphicObject * object = 0;
	switch( geometryObject->getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GraphicPoint( geometryObject, canvas );
			break;
		case GEOMETRYOBJECT_POINT_HIGHLIGHTED:
				object = new GraphicPointHighlighted( geometryObject, canvas );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GraphicLink( geometryObject, canvas );
			break;
	}
	return object;
}

GeometryObjectFactory & GeometryObjectFactory::getInstance()
{
	static GeometryObjectFactory instance;
	return instance;
}














