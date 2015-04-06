/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"
#include <string.h>

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space ),
		m_ConstraintFrom( 0 ), m_ConstraintTo( 0 ), m_ConstraintFromTo( 0 )
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
	if( 0 != m_ConstraintFromTo && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFromTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFromTo );
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
	}
	if( 0 != m_ConstraintFrom && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFrom ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFrom );
		cpConstraintFree( m_ConstraintFrom );
		m_ConstraintFrom = 0;
	}
	if( 0 != m_ConstraintTo && true == cpSpaceContainsConstraint( m_Space, m_ConstraintTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintTo );
		cpConstraintFree( m_ConstraintTo );
		m_ConstraintTo = 0;
	}

//	if( true == cpSpaceContainsShape( m_Space, m_Shape ) )
//	{
//		cpSpaceRemoveShape( m_Space, m_Shape );
//		cpShapeFree( m_Shape );
//		m_Shape = 0;
//	}
//	if( true == cpSpaceContainsBody( m_Space, m_Body ) )
//	{
//		cpSpaceRemoveBody( m_Space, m_Body );
//		cpBodyFree( m_Body );
//		m_Body = 0;
//	}
}

void GeometryLinkDynamic::initGround()
{
	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.

	cpFloat radius = 1.0;
	cpFloat mass = 0.0;
	cpVect startPoint = cpv( getPointFrom()->getX(), getPointFrom()->getY() );
	cpVect endPoint = cpv( getPointTo()->getX(), getPointTo()->getY() );
	cpFloat moment = cpMomentForSegment( mass, startPoint, endPoint, radius );
	m_Body = cpBodyNew( mass, moment );

	cpSpaceAddBody( m_Space, m_Body );

	m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );


	cpShapeSetFriction( m_Shape, 1 );
	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometryLinkDynamic::initJoints()
{
	if( 0 != getDynamicPointFrom() && 0 != getDynamicPointTo() )
	{
//		cpVect pointJointFrom = cpBodyLocalToWorld( getDynamicPointFrom()->getBody(), cpvzero );
//		cpVect pointJointTo = cpBodyLocalToWorld( getDynamicPointTo()->getBody(), cpvzero );
//		int middle_x = abs( getDynamicPointTo()->getX() - getDynamicPointFrom()->getX() ) / 2;
//		int middle_y = abs( getDynamicPointTo()->getY() - getDynamicPointFrom()->getY() ) / 2;
//		cpVect pointJoint = cpv( 0, 0 );
//		m_ConstraintFrom = cpSpaceAddConstraint( m_Space, cpPinJointNew( m_Body, getDynamicPointFrom()->getBody(), cpvzero, cpvzero ) );

//		m_ConstraintTo = cpSpaceAddConstraint( m_Space, cpPinJointNew( m_Body, getDynamicPointTo()->getBody(), cpvzero, cpvzero ) );

		m_ConstraintFromTo = cpSpaceAddConstraint( m_Space, cpPinJointNew( getDynamicPointTo()->getBody(), getDynamicPointFrom()->getBody(), cpvzero, cpvzero ) );
	}
}

void GeometryLinkDynamic::clearJoints()
{
//	if( m_ConstraintFrom != 0 )
//	{
//		cpConstraintFree( m_ConstraintFrom );
//		m_ConstraintFrom = 0;
//	}
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
	GeometryObjectDynamicBase::update();
}










