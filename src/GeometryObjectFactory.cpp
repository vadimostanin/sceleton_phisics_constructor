/*
 * GeometryObjectFactory.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFactory.h"

#include "GraphicLink.h"
#include "Point.h"
#include "GeometryLink.h"
#include "GraphicPoint.h"
#include "GraphicPointHighlighted.h"

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
				object = new GeometryLink();
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














