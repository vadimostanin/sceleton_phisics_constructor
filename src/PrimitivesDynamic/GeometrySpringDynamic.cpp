/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometrySpringDynamic.h"
#include "GeometrySpringGetAngles.h"
#include "GetRotateAngleFunctor.h"
#include <string.h>
#include <iostream>

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space, GeometrySpring * geometrySpring ) : GeometrySpring( geometrySpring->getLinkFrom(), geometrySpring->getLinkTo() ), m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintGear( 0 )
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
	GeometrySpringGetAngles getAngles( this );
	int linkFromAbsoluteAngle = getAngles.getLinkFromAngle();
	int linkToAbsoluteAngle = getAngles.getLinkToAngle();

	int angleInt = abs( linkFromAbsoluteAngle - linkToAbsoluteAngle );
	float angle = M_PI / 180.0 * angleInt;

	const GeometryLinkDynamic * linkFrom = getDynamicLinkFrom();
	const GeometryLinkDynamic * linkTo = getDynamicLinkTo();

	cpBody * bodyFrom = linkFrom->getBody();
	cpBody * bodyTo = linkTo->getBody();

	GetRotateAngleFunctor getAngle( this );
	int rotateAngleInt = getAngle.getAngle();
	float rotateAngle  = M_PI / 180.0 * rotateAngleInt;

	m_ConstraintGear = cpSpaceAddConstraint( m_Space, cpGearJointNew( bodyFrom, bodyTo, rotateAngle, 1.0f ) );

}

void GeometrySpringDynamic::initJoints()
{
	if( 0 != getDynamicLinkFrom() && 0 != getDynamicLinkTo() )
	{
		initSpring();
	}
}

void GeometrySpringDynamic::clearJoints()
{
	if( 0 != m_ConstraintGear && true == cpSpaceContainsConstraint( m_Space, m_ConstraintGear ) )
	{
		cpSpaceRemoveConstraint( m_Space, m_ConstraintGear );
		cpConstraintFree( m_ConstraintGear );
		m_ConstraintGear = 0;
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










