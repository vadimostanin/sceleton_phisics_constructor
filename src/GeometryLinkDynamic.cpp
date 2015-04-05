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
//    setId( geometryLink->getId );

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

	cpBodyNew( 1, 1.0)

	m_Ground = cpSegmentShapeNew( cpSpaceGetStaticBody( m_Space ), cpv( getPointFrom()->getX(), getPointFrom()->getY() ), cpv( getPointTo()->getX(), getPointTo()->getY() ), 0 );



	cpShapeSetFriction( m_Ground, 1 );
	cpSpaceAddShape( m_Space, m_Ground );
}

void GeometryLinkDynamic::initLink()
{
	cpsp
}

void GeometryLinkDynamic::setDynamicPointFrom( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[0] = dynamicPoint;
    setPointFrom( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );
}

void GeometryLinkDynamic::setDynamicPointTo( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[1] = dynamicPoint;
    setPointTo( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );
}

const IGeometryObject & GeometryLinkDynamic::getGeometryObject() const
{
	return *this;
}

void GeometryLinkDynamic::update()
{
//	 cpVect pos = cpBodyGetPosition( m_BallBody );
//	 cpVect vel = cpBodyGetVelocity( m_BallBody );

// 	cpFloat timeStep = 1.0/60.0;//0.01666

 	cpSpaceStep( m_Space, (1.0/30.0) / 4.0 );

// 	setX( pos.x );
// 	setY( pos.y );
}










