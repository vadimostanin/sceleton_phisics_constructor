/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space )
{
	initGround();
}

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink ) : m_Space( space )
{
	setPointFrom( geometryLink->getPointFrom() );
	setPointTo( geometryLink->getPointTo() );

	initGround();
}

GeometryLinkDynamic::~GeometryLinkDynamic()
{
	cpShapeFree( m_Ground );
}

void GeometryLinkDynamic::initGround()
{
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
	m_Ground = cpSegmentShapeNew( cpSpaceGetStaticBody( m_Space ), cpv( getPointFrom()->getX(), getPointFrom()->getY() ), cpv( getPointTo()->getX(), getPointTo()->getY() ), 0 );

	cpShapeSetFriction( m_Ground, 1 );
	cpSpaceAddShape( m_Space, m_Ground );
}

void GeometryLinkDynamic::setDynamicPointFrom( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[0] = dynamicPoint;
}

void GeometryLinkDynamic::setDynamicPointTo( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[1] = dynamicPoint;
}

IGeometryObject & GeometryLinkDynamic::getGeometryObject()
{
	return *this;
}

void GeometryLinkDynamic::update()
{
	;
}










