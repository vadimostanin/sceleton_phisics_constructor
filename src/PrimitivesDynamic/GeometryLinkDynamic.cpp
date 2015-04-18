/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryLinkDynamic.h"
#include <string.h>
#include <iostream>

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
}

GeometryLinkDynamic::GeometryLinkDynamic( cpSpace * space, GeometryLink * geometryLink ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintFrom( 0 ), m_ConstraintTo( 0 )
{
	memset( m_DynamicPoints, 0, sizeof( m_DynamicPoints ) );
	setPointFrom( geometryLink->getPointFrom() );
	setPointTo( geometryLink->getPointTo() );
    setId( geometryLink->getId() );
}

GeometryLinkDynamic::~GeometryLinkDynamic()
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

void GeometryLinkDynamic::initLink()
{
	cpFloat ballRadius = getDynamicPointFrom()->getRadius();

	cpFloat mass = 1;

	int box_width = getWidth();
	int box_height = 2;

	cpFloat moment = cpMomentForBox( mass, box_width - ballRadius * 2, box_height );
	m_Body = cpBodyNew( mass, moment );

	int from_x = getPointFrom()->getX();
	int to_x = getPointTo()->getX();
	int from_y = getPointFrom()->getY();
	int to_y = getPointTo()->getY();

	int from_to_center_x = ( from_x + to_x ) / 2;
	int from_to_center_y = ( from_y + to_y ) / 2;

	cpBodySetPosition( m_Body, cpv( from_to_center_x, from_to_center_y ) );


	cpSpaceAddBody( m_Space, m_Body );

//	m_Shape = cpBoxShapeNew( m_Body, box_width, box_height, 0.0 );
//
//
//	cpShapeSetFriction( m_Shape, 1 );
//	cpSpaceAddShape( m_Space, m_Shape );
}

void GeometryLinkDynamic::initJoints()
{
	if( 0 == getDynamicPointFrom() || 0 == getDynamicPointTo() )
	{
		return;
	}
	initLink();

	cpFloat ballRadius = getDynamicPointFrom()->getRadius();

	int box_width = getWidth();

	cpVect fromLink = cpv( ( -1 ) * box_width + ( box_width / 2 ) + ballRadius, 0 );
	cpVect toLink = cpv( box_width - ( box_width / 2 ) - ballRadius, 0 );

	cpVect fromPoint = cpv( 0, 0 );
	cpVect toPoint = cpv( 0, 0 );

	m_ConstraintFrom = cpPivotJointNew2( m_Body, getDynamicPointFrom()->getBody(), fromLink, fromPoint );
	m_ConstraintTo   = cpPivotJointNew2( m_Body, getDynamicPointTo()->getBody(), toLink, toPoint );
	cpSpaceAddConstraint( m_Space, m_ConstraintFrom );
	cpSpaceAddConstraint( m_Space, m_ConstraintTo );
}
/*
void GeometryLinkDynamic::initJoints()
{
	if( 0 == getDynamicPointFrom() || 0 == getDynamicPointTo() )
	{
		return;
	}
	initLink();

	cpFloat ballRadius = getDynamicPointFrom()->getRadius();

	int from_x = getPointFrom()->getX();
	int to_x = getPointTo()->getX();
	int from_y = getPointFrom()->getY();
	int to_y = getPointTo()->getY();

	int from_to_center_x = ( from_x + to_x ) / 2;
	int from_to_center_y = ( from_y + to_y ) / 2;

	int katet_width = abs( from_x - to_x );
	int katet_height = abs( from_y - to_y );

	int box_width = sqrt( katet_height * katet_height + katet_width * katet_width );

	cpVect fromLink = cpv( from_to_center_x + ( -1 ) * box_width + ( box_width / 2 ) + ballRadius, from_to_center_y );
	cpVect toLink = cpv( from_to_center_x + box_width - ( box_width / 2 ) - ballRadius, from_to_center_y );

	cpVect fromPoint = cpv( from_x, from_y );
	cpVect toPoint = cpv( to_x, to_y );

	m_ConstraintFrom = cpPivotJointNew2( m_Body, getDynamicPointFrom()->getBody(), fromLink, fromPoint );
	m_ConstraintTo   = cpPivotJointNew2( m_Body, getDynamicPointTo()->getBody(), toLink, toPoint );
	cpConstraintSetMaxBias( m_ConstraintFrom, INFINITY );
	cpConstraintSetMaxBias( m_ConstraintTo, INFINITY );
	cpConstraintSetMaxForce( m_ConstraintFrom, INFINITY );
	cpConstraintSetMaxForce( m_ConstraintTo, INFINITY );
	cpSpaceAddConstraint( m_Space, m_ConstraintFrom );
	cpSpaceAddConstraint( m_Space, m_ConstraintTo );
}
*/

void GeometryLinkDynamic::clearJoints()
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

const GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointFrom() const
{
	return m_DynamicPoints[0];
}

const GeometryPointDynamic * GeometryLinkDynamic::getDynamicPointTo() const
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
//	cpFloat moment = cpShapeGetMoment( m_Shape );
//	cout << "link moment=" << moment << endl << flush;
}










