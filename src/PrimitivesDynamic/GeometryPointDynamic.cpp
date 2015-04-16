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

GeometryPointDynamic::GeometryPointDynamic( cpSpace * space, GeometryPoint * geometryPoint ) :
		m_Space( space ), m_BallBody( 0 ), m_BallShape( 0 ), m_Radius( 10 ), m_Mass( 1 ),
		m_Ephysics_World( 0 ), m_Ephysics_Body( 0 )
{
	setX( geometryPoint->getX() );
	setY( geometryPoint->getY() );
	setId( geometryPoint->getId() );

	initPoint();
}

GeometryPointDynamic::GeometryPointDynamic( EPhysics_World * world, GeometryPoint * geometryPoint ) :
		m_Space( 0 ), m_BallBody( 0 ), m_BallShape( 0 ), m_Radius(8 ), m_Mass( 1 ),
		m_Ephysics_World( world ), m_Ephysics_Body( 0 )
{
	setX( geometryPoint->getX() );
	setY( geometryPoint->getY() );
	setId( geometryPoint->getId() );

	initEphysicsPoint();
}

GeometryPointDynamic::~GeometryPointDynamic()
{
	if( 0 != m_Space )
	{
		cpSpaceRemoveShape( m_Space, m_BallShape );
		cpShapeFree( m_BallShape );
		cpSpaceRemoveBody( m_Space, m_BallBody );
		cpBodyFree( m_BallBody );
	}
	if( 0 != m_Ephysics_Body )
	{
		ephysics_body_del( m_Ephysics_Body );
	}
}

const IGeometryObject & GeometryPointDynamic::getGeometryObject() const
{
	return *this;
}

GeometryPointDynamic * lpThis = 0;

void GeometryPointDynamic::update()
{
//	cpVect pos = cpBodyGetPosition( m_BallBody );
//
//	setX( pos.x );
//	setY( pos.y );

	Evas_Coord x = 0, y = 0, z = 0, w = 0, h = 0, d = 0;
	ephysics_body_geometry_get( m_Ephysics_Body, &x, &y, &z, &w, &h, &d );

	setX( x );
	setY( y );
	cout << "x=" << x << "; y=" << y << endl << flush;
}

void GeometryPointDynamic::initPoint()
{
	lpThis = this;
	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle( m_Mass, 0, m_Radius, cpvzero );

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
}

void GeometryPointDynamic::initEphysicsPoint()
{
	m_Ephysics_Body = ephysics_body_sphere_add( m_Ephysics_World );
	ephysics_body_mass_set( m_Ephysics_Body, m_Mass );
	ephysics_body_restitution_set( m_Ephysics_Body, 0.5 );
	ephysics_body_friction_set( m_Ephysics_Body, 0.1 );

	int x = getX();
	int y = getY();

	ephysics_body_geometry_set( m_Ephysics_Body, x, y, 0, getRadius(), getRadius(), 1 );
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
















