/*
 * DynamicObjectFactory.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "DynamicObjectFactory.h"
#include "GeometryPointDynamic.h"

DynamicObjectFactory::DynamicObjectFactory()
{
	initSpace();
	initGround();
}

DynamicObjectFactory::~DynamicObjectFactory()
{
}

void DynamicObjectFactory::initSpace()
{
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	m_Gravity = cpv( 0, -1000 );
	// Create an empty space.
	m_Space = cpSpaceNew();
	cpSpaceSetGravity( m_Space, m_Gravity );
}

void DynamicObjectFactory::initGround()
{
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
	cpShape *ground = cpSegmentShapeNew( cpSpaceGetStaticBody( m_Space ), cpv(-1000, 0), cpv(1000, 0), 0);

	cpShapeSetFriction( ground, 1 );
	cpSpaceAddShape( m_Space, ground);
}

IDynamicGeometryObject * DynamicObjectFactory::createObject( GeometryObjectsTypes type )
{
	IDynamicGeometryObject * object = NULL;

	switch( type )
	{
		case GEOMETRYOBJECT_POINT:
				object = new GeometryPointDynamic( m_Space );
			break;
		case GEOMETRYOBJECT_LINK:
			break;
		case GEOMETRYOBJECT_SPRING:
			break;
		default:
			break;
	}

	return object;
}

DynamicObjectFactory & DynamicObjectFactory::getInstance()
{
	static DynamicObjectFactory instance;
	return instance;
}
















