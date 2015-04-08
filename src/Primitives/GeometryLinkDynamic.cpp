/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"
#include <string.h>

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	initLink();
}

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	setPointFrom( geometryLink->getPointFrom() );
	setPointTo( geometryLink->getPointTo() );
    setId( geometryLink->getId() );

	initLink();
}

GeometryLinkDynamic::~GeometryLinkDynamic()
{
	if( 0 != m_ConstraintFromTo && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFromTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFromTo );
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
	}

	if( true == cpSpaceContainsShape( m_Space, m_Shape ) )
	{
		cpSpaceRemoveShape( m_Space, m_Shape );
		cpShapeFree( m_Shape );
		m_Shape = 0;
	}
	if( true == cpSpaceContainsBody( m_Space, m_Body ) )
	{
		cpSpaceRemoveBody( m_Space, m_Body );
		cpBodyFree( m_Body );
		m_Body = 0;
	}
}

void GeometryLinkDynamic::initLink()
{
	cpFloat radius = 5.0;
	cpFloat mass = 1000;
	cpVect startPoint = cpv( getPointFrom()->getX(), getPointFrom()->getY() );
	cpVect endPoint = cpv( getPointTo()->getX(), getPointTo()->getY() );
	cpFloat moment = cpMomentForSegment( mass, startPoint, endPoint, radius );
	m_Body = cpBodyNew( mass, moment );

	cpSpaceAddBody( m_Space, m_Body );

	m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );


//	cpShapeSetFriction( m_Shape, 100 );
//	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometryLinkDynamic::initJoints()
{
	if( 0 != getDynamicPointFrom() && 0 != getDynamicPointTo() )
	{
		m_ConstraintFromTo = cpSpaceAddConstraint( m_Space, cpPinJointNew( getDynamicPointTo()->getBody(), getDynamicPointFrom()->getBody(), cpvzero, cpvzero ) );
	}
}

void GeometryLinkDynamic::clearJoints()
{
	if( m_ConstraintFromTo != 0 )
	{
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
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

cpBody * GeometryLinkDynamic::getBody() const
{
	return m_Body;
}

cpShape * GeometryLinkDynamic::getShape() const
{
	return m_Shape;
}

cpSpace * GeometryLinkDynamic::getSpace() const
{
	return m_Space;
}

const IGeometryObject & GeometryLinkDynamic::getGeometryObject() const
{
	return *this;
}

void GeometryLinkDynamic::update()
{

}










