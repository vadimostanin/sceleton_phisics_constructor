/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"
#include <string.h>

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space ),
		m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	initGround();
}

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink ) : m_Space( space ),
		m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	setPointFrom( geometryLink->getPointFrom() );
	setPointTo( geometryLink->getPointTo() );
//    setId( geometryLink->getId() );

	initGround();
}

GeometryLinkDynamic::~GeometryLinkDynamic()
{
	cpBodyFree( m_Body );
	cpShapeFree( m_Shape );
}

void GeometryLinkDynamic::initGround()
{
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.

	cpFloat radius = 1.0;
	cpFloat mass = 1.0;
	cpVect startPoint = cpv( getPointFrom()->getX(), getPointFrom()->getY() );
	cpVect endPoint = cpv( getPointTo()->getX(), getPointTo()->getY() );
	cpFloat moment = cpMomentForSegment( mass, startPoint, endPoint, radius );
	m_Body = cpBodyNew( mass, moment );

	m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );


	cpShapeSetFriction( m_Shape, 1 );
	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometryLinkDynamic::initJoints()
{
	if( 0 != getDynamicPointFrom() && 0 != getDynamicPointTo() )
	{
		m_ConstraintFrom = cpSpaceAddConstraint( m_Space, cpPivotJointNew( getDynamicPointFrom()->getBody(), m_Body, cpvzero ) );

		m_ConstraintTo = cpSpaceAddConstraint( m_Space, cpPivotJointNew( getDynamicPointTo()->getBody(), m_Body, cpvzero ) );
	}
}

void GeometryLinkDynamic::clearJoints()
{
	if( m_ConstraintFrom != 0 )
	{
		cpConstraintFree( m_ConstraintFrom );
		m_ConstraintFrom = 0;
	}
	if( m_ConstraintTo != 0 )
	{
		cpConstraintFree( m_ConstraintTo );
		m_ConstraintTo = 0;
	}
}

void GeometryLinkDynamic::setDynamicPointFrom( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[0] = dynamicPoint;
    setPointFrom( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );

    clearJoints();
    initJoints();
}

void GeometryLinkDynamic::setDynamicPointTo( GeometryPointDynamic * dynamicPoint )
{
	m_DynamicPoints[1] = dynamicPoint;
    setPointTo( (const GeometryPoint *)&dynamicPoint->getGeometryObject() );

    clearJoints();
    initJoints();
}

GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointFrom() const
{
	return m_DynamicPoints[0];
}

GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointTo() const
{
	return m_DynamicPoints[1];
}

const IGeometryObject & GeometryLinkDynamic::getGeometryObject() const
{
	return *this;
}

void GeometryLinkDynamic::update()
{
 	cpSpaceStep( m_Space, (1.0/30.0) / 4.0 );
}










