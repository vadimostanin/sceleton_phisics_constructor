/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometrySpringDynamic.h"
#include "DynamicSpringGetCrosslinkPredicate.h"
#include <string.h>
#include <iostream>

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicLinks, 0, sizeof( m_DynamicLinks ) );
}

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space, GeometrySpring * geometrySpring ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicLinks, 0, sizeof( m_DynamicLinks ) );
	setLinkFrom( geometrySpring->getLinkFrom() );
	setLinkTo( geometrySpring->getLinkTo() );
    setId( geometrySpring->getId() );
}

GeometrySpringDynamic::~GeometrySpringDynamic()
{
	clearJoints();

	if( 0 != m_Shape && true == cpSpaceContainsShape( m_Space, m_Shape ) )
	{
		cpSpaceRemoveShape( m_Space, m_Shape );
		cpShapeFree( m_Shape );
		m_Shape = 0;
	}
	if( 0 != m_Body && true == cpSpaceContainsBody( m_Space, m_Body ) )
	{
		cpSpaceRemoveBody( m_Space, m_Body );
		cpBodyFree( m_Body );
		m_Body = 0;
	}
}

void GeometrySpringDynamic::initSpring()
{
//     cpFloat radius = 0.0;
	   cpFloat mass = 1.0;
	   int from_x = ( getLinkFrom()->getPointFrom()->getX() + getLinkFrom()->getPointTo()->getX() ) / 2;
	   int from_y = ( getLinkFrom()->getPointFrom()->getY() + getLinkFrom()->getPointTo()->getY() ) / 2;
//
	   int to_x = ( getLinkTo()->getPointFrom()->getX() + getLinkTo()->getPointTo()->getX() ) / 2;
	   int to_y = ( getLinkTo()->getPointFrom()->getY() + getLinkTo()->getPointTo()->getY() ) / 2;

	   int katet_width = abs( from_x - to_x );
	   int katet_height = abs( from_y - to_y );

	   int box_width = sqrt( katet_height * katet_height + katet_width * katet_width );
	  int box_height = 2;

	   cpVect startPoint = cpv( from_x, from_y );
	   cpVect endPoint = cpv( to_x, to_y );
	   cpFloat moment = cpMomentForBox( mass, box_width, box_height );
	   m_Body = cpBodyNew( mass, moment );

	   int from_to_center_x = ( from_x + to_x ) / 2;
	   int from_to_center_y = ( from_y + to_y ) / 2;

	   cpBodySetPosition( m_Body, cpv( from_to_center_x, from_to_center_y ) );

	   cpSpaceAddBody( m_Space, m_Body );
//
//     m_Shape = cpSegmentShapeNew( m_Body, startPoint, endPoint, radius );
//
//
////   cpShapeSetFriction( m_Shape, 0 );
//     cpSpaceAddShape( m_Space, m_Shape );
}

void GeometrySpringDynamic::initJoints()
{
	if( 0 != getDynamicLinkFrom() && 0 != getDynamicLinkTo() )
	{
		initSpring();

		cpFloat ballRadius = 2.0;

		int from_x = ( getLinkFrom()->getPointFrom()->getX() + getLinkFrom()->getPointTo()->getX() ) / 2;
		int from_y = ( getLinkFrom()->getPointFrom()->getY() + getLinkFrom()->getPointTo()->getY() ) / 2;

		int to_x = ( getLinkTo()->getPointFrom()->getX() + getLinkTo()->getPointTo()->getX() ) / 2;
		int to_y = ( getLinkTo()->getPointFrom()->getY() + getLinkTo()->getPointTo()->getY() ) / 2;

		int katet_width = abs( from_x - to_x );
		int katet_height = abs( from_y - to_y );

		int box_width = sqrt( katet_height * katet_height + katet_width * katet_width );

		cpVect fromSpring = cpv( ( -1 ) * box_width + ( box_width / 2 ) + ballRadius, 0 );
		cpVect toSpring = cpv( box_width - ( box_width / 2 ) - ballRadius, 0 );

		cpVect fromPoint = cpv( 0, 0 );
		cpVect toPoint = cpv( 0, 0 );

		m_ConstraintFrom = cpPivotJointNew2( m_Body, getDynamicLinkFrom()->getBody(), fromSpring, fromPoint );
		m_ConstraintTo   = cpPivotJointNew2( m_Body, getDynamicLinkTo()->getBody(), toSpring, toPoint );

		cpSpaceAddConstraint( m_Space, m_ConstraintFrom );
		cpSpaceAddConstraint( m_Space, m_ConstraintTo );

		cpVect globalStart = cpBodyWorldToLocal( m_Body, fromSpring );
		cpVect globalEnd = cpBodyWorldToLocal( m_Body, toSpring );
		int a = 0;
		a++;
	}
}

void GeometrySpringDynamic::clearJoints()
{
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

const GeometryLinkDynamic * GeometrySpringDynamic::getDynamicLinkFrom() const
{
	return m_DynamicLinks[0];
}

const GeometryLinkDynamic * GeometrySpringDynamic::getDynamicLinkTo() const
{
	return m_DynamicLinks[1];
}

const IGeometryObject & GeometrySpringDynamic::getGeometryObject() const
{
	return *this;
}

void GeometrySpringDynamic::update()
{
//	cpFloat restLength = cpDampedSpringGetRestLength( m_ConstraintFromTo );
//	cout << "restLength=" << restLength << endl << flush;
}










