/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometrySpringDynamic.h"
#include <string.h>
#include <iostream>

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicLinks, 0, sizeof( m_DynamicLinks ) );
	initSpring();
}

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space, GeometrySpring * geometrySpring ) : m_Space( space ), m_ConstraintFromTo( 0 )
{
	memset( m_DynamicLinks, 0, sizeof( m_DynamicLinks ) );
	setLinkFrom( geometrySpring->getLinkFrom() );
	setLinkTo( geometrySpring->getLinkTo() );
//    setId( geometryLink->getId() );

	initSpring();
}

GeometrySpringDynamic::~GeometrySpringDynamic()
{
	if( 0 != m_ConstraintFromTo && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFromTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFromTo );
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
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

void GeometrySpringDynamic::initSpring()
{
//	cpFloat radius = 0.0;
//	cpFloat mass = 1.0;
//	int from_x = ( getLinkFrom()->getPointFrom()->getX() + getLinkFrom()->getPointTo()->getX() ) / 2;
//	int from_y = ( getLinkFrom()->getPointFrom()->getY() + getLinkFrom()->getPointTo()->getY() ) / 2;
//
//	int to_x = ( getLinkTo()->getPointFrom()->getX() + getLinkTo()->getPointTo()->getX() ) / 2;
//	int to_y = ( getLinkTo()->getPointFrom()->getY() + getLinkTo()->getPointTo()->getY() ) / 2;
//
//	cpVect startPoint = cpv( from_x, from_y );
//	cpVect endPoint = cpv( to_x, to_y );
//	cpFloat moment = cpMomentForSegment( mass, startPoint, endPoint, radius );
//	m_Body = cpBodyNew( mass, moment );
//
//	cpSpaceAddBody( m_Space, m_Body );
//
//	m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );
//
//
////	cpShapeSetFriction( m_Shape, 0 );
//	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometrySpringDynamic::initJoints()
{
	if( 0 != getDynamicLinkFrom() && 0 != getDynamicLinkTo() )
	{
		int from_x = ( getLinkFrom()->getPointFrom()->getX() + getLinkFrom()->getPointTo()->getX() ) / 2;
		int from_y = ( getLinkFrom()->getPointFrom()->getY() + getLinkFrom()->getPointTo()->getY() ) / 2;

		int to_x = ( getLinkTo()->getPointFrom()->getX() + getLinkTo()->getPointTo()->getX() ) / 2;
		int to_y = ( getLinkTo()->getPointFrom()->getY() + getLinkTo()->getPointTo()->getY() ) / 2;

		m_ConstraintFromTo = cpSpaceAddConstraint( m_Space, cpDampedSpringNew( getDynamicLinkTo()->getBody(), getDynamicLinkFrom()->getBody(), cpvzero, cpvzero, 10, 10, 1.0 ) );
	}
}

void GeometrySpringDynamic::clearJoints()
{
	if( m_ConstraintFromTo != 0 && true == cpSpaceContainsConstraint( m_Space, m_ConstraintFromTo ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintFromTo );
		cpConstraintFree( m_ConstraintFromTo );
		m_ConstraintFromTo = 0;
	}
}

void GeometrySpringDynamic::setDynamicLinkFrom( GeometryLinkDynamic * dynamicLink )
{
	m_DynamicLinks[0] = dynamicLink;
    setLinkFrom( (const GeometryLink *)&dynamicLink->getGeometryObject() );

    clearJoints();
    initJoints();
}

void GeometrySpringDynamic::setDynamicLinkTo( GeometryLinkDynamic * dynamicLink )
{
	m_DynamicLinks[1] = dynamicLink;
    setLinkTo( (const GeometryLink *)&dynamicLink->getGeometryObject() );

    clearJoints();
    initJoints();
}

GeometryLinkDynamic * GeometrySpringDynamic::getDynamicLinkFrom() const
{
	return m_DynamicLinks[0];
}

GeometryLinkDynamic * GeometrySpringDynamic::getDynamicLinkTo() const
{
	return m_DynamicLinks[1];
}

const IGeometryObject & GeometrySpringDynamic::getGeometryObject() const
{
	return *this;
}

void GeometrySpringDynamic::update()
{
	cpFloat restLength = cpDampedSpringGetRestLength( m_ConstraintFromTo );
	cout << "restLength=" << restLength << endl << flush;
}










