/*
 * GeometryPointDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryPointDynamic.h"
#include <cstdio>
#include <iostream>
using namespace std;

GeometryPointDynamic::GeometryPointDynamic( cpSpace * space ) : m_Space( space ), m_Radius( 8 ), m_Mass( 1 )
{
	initPoint();
}

GeometryPointDynamic::GeometryPointDynamic( cpSpace * space, GeometryPoint * geometryPoint ) : m_Space( space ), m_Radius( 8 ), m_Mass( 1 )
{
	setX( geometryPoint->getX() );
	setY( geometryPoint->getY() );
	setId( geometryPoint->getId() );

	initPoint();
}

GeometryPointDynamic::~GeometryPointDynamic()
{
	cpSpaceRemoveShape( m_Space, m_BallShape );
	cpShapeFree( m_BallShape );
	cpSpaceRemoveBody( m_Space, m_BallBody );
	cpBodyFree( m_BallBody );
}

const IGeometryObject & GeometryPointDynamic::getGeometryObject() const
{
	return *this;
}

static GeometryPointDynamic * lpThis = 0;

void GeometryPointDynamic::update()
{
	cpVect pos = cpBodyGetPosition( m_BallBody );
//	cpVect vel = cpBodyGetVelocity( m_BallBody );

	setX( pos.x );
	setY( pos.y );
}

void GeometryPointDynamic::initPoint()
{
	lpThis = this;
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle( m_Mass, 0, m_Radius, cpvzero );
	cpFloat emptyBodyMoment = cpMomentForCircle( m_Mass, 0, 0.1, cpvzero );

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	m_BallBody = cpSpaceAddBody( m_Space, cpBodyNew( m_Mass, moment ) );
//	m_OuterBody = cpSpaceAddBody( m_Space, cpBodyNew( m_Mass, emptyBodyMoment ) );
	cpBodySetPosition( m_BallBody, cpv( getX(), getY() ) );
//	cpBodySetPosition( m_OuterBody, cpv( getX(), getY() ) );

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	m_BallShape = cpSpaceAddShape( m_Space, cpCircleShapeNew( m_BallBody, m_Radius, cpvzero ) );
	cpShapeSetFriction( m_BallShape, 1.0 );

	cpShapeSetElasticity( m_BallShape, 0.3 );

//	m_TrackingBody = cpShapeGetBody( shape );
//
//
//	m_IntermidiateConstraint = cpSpaceAddConstraint( m_Space, cpPivotJointNew2( m_BallBody, m_OuterBody, cpvzero, cpvzero ) );
}

cpFloat GeometryPointDynamic::getRadius() const
{
	return m_Radius;
}

cpFloat GeometryPointDynamic::getMass() const
{
	return m_Mass;
}

cpBody * GeometryPointDynamic::getBody() const
{
	return m_BallBody;
}

cpShape * GeometryPointDynamic::getShape() const
{
	return m_BallShape;
}

cpSpace * GeometryPointDynamic::getSpace() const
{
	return m_Space;
}
















