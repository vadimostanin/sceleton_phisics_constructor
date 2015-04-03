/*
 * GeometryPointDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryPointDynamic.h"
#include <cstdio>

//GeometryPointDynamic::GeometryPointDynamic() : m_Space( NULL ), m_BallBody( NULL ), m_Radius( 5 ), m_Mass( 1 )
//{
//}

GeometryPointDynamic::GeometryPointDynamic( cpSpace * space ) : m_Space( space ), m_Radius( 5 ), m_Mass( 1 )
{
	initPoint();
}

GeometryPointDynamic::GeometryPointDynamic( cpSpace * space, GeometryPoint * geometryPoint ) : m_Space( space ), m_Radius( 5 ), m_Mass( 10 )
{
	setX( geometryPoint->getX() );
	setY( geometryPoint->getY() );
	setId( geometryPoint->getId() );

	initPoint();
}

GeometryPointDynamic::~GeometryPointDynamic()
{
	// Clean up our objects and exit!
	cpShapeFree( m_BallShape );
	cpBodyFree( m_BallBody );
}

IGeometryObject & GeometryPointDynamic::getGeometryObject()
{
	return *this;
}

void GeometryPointDynamic::update()
{
	cpVect pos = cpBodyGetPosition( m_BallBody );
	cpVect vel = cpBodyGetVelocity( m_BallBody );


	printf(
	  "Time is  ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
	  pos.x, pos.y, vel.x, vel.y
	); fflush( stdout );

	cpFloat timeStep = 1.0/60.0;

	cpSpaceStep( m_Space, timeStep);

	setX( pos.x );
	setY( pos.y );
}

void GeometryPointDynamic::initPoint()
{
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle( m_Mass, 0, m_Radius, cpvzero );

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	m_BallBody = cpSpaceAddBody( m_Space, cpBodyNew( m_Mass, moment ) );
	cpBodySetPosition( m_BallBody, cpv( getX(), getY() ) );

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	m_BallShape = cpSpaceAddShape( m_Space, cpCircleShapeNew( m_BallBody, m_Radius, cpvzero ) );
	cpShapeSetFriction( m_BallShape, 0.7 );
}
















