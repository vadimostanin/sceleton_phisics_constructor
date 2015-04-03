/*
 * DynamicObjectFactory.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "DynamicObjectFactory.h"
#include "GeometryPointDynamic.h"
#include "GeometryLinkDynamic.h"
#include "GraphicPointDynamic.h"
#include "GraphicLinkDynamic.h"

DynamicObjectFactory::DynamicObjectFactory() : m_Space( 0 ), m_CanvasWidth( 0 ), m_CanvasHeight( 0 ), m_Inited( false )
{
}

DynamicObjectFactory::~DynamicObjectFactory()
{
	cpSpaceFree( m_Space );
}

void DynamicObjectFactory::init()
{
	if( true == m_Inited )
	{
		return;
	}
	initSpace();

	m_Inited = true;
}

void DynamicObjectFactory::initSpace()
{
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	m_Gravity = cpv( 0, 100 );
	// Create an empty space.
	m_Space = cpSpaceNew();
	cpSpaceSetGravity( m_Space, m_Gravity );
}

IDynamicObject * DynamicObjectFactory::createDynamicObject( IGeometryObject * geometryObject )
{
	IDynamicObject * object = 0;
	switch( geometryObject->getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GeometryPointDynamic( m_Space, (GeometryPoint *)geometryObject );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GeometryLinkDynamic( m_Space, (GeometryLink *)geometryObject );
			break;
		default:
			break;
	}
	return object;
}

IDynamicObject * DynamicObjectFactory::createObject( GeometryObjectsTypes type )
{
	IDynamicObject * object = NULL;

	switch( type )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GeometryPointDynamic( m_Space );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GeometryLinkDynamic( m_Space );
			break;
		case GEOMETRYOBJECT_SPRING:
			break;
		default:
			break;
	}

	return object;
}


IGraphicObject * DynamicObjectFactory::createGraphicObject( IDynamicObject * dynamicObject, Evas_Object * canvas )
{
	IGraphicObject * object = 0;
	switch( dynamicObject->getGeometryObject().getType() )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GraphicPointDynamic( (GeometryPointDynamic *)dynamicObject, canvas );
			break;
		case GEOMETRYOBJECT_LINK:
				object = new GraphicLinkDynamic( (GeometryLinkDynamic *)dynamicObject, canvas );
			break;
		default:
			break;
	}
	return object;
}

void DynamicObjectFactory::setCanvasWidth( unsigned int width )
{
	m_CanvasWidth = width;
}

void DynamicObjectFactory::setCanvasHeight( unsigned int height )
{
	m_CanvasHeight = height;
}

unsigned int DynamicObjectFactory::getCanvasWidth() const
{
	return m_CanvasWidth;
}

unsigned int DynamicObjectFactory::getCanvasHeight() const
{
	return m_CanvasHeight;
}

DynamicObjectFactory & DynamicObjectFactory::getInstance()
{
	static DynamicObjectFactory instance;
	return instance;
}
















