/*
 * GeometryLinkDynamic.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometrySpringDynamic.h"
#include <string.h>
#include <iostream>

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintGear( 0 )
{
	memset( m_DynamicLinks, 0, sizeof( m_DynamicLinks ) );
}

GeometrySpringDynamic::GeometrySpringDynamic( cpSpace * space, GeometrySpring * geometrySpring ) : m_Space( space ), m_Body( 0 ), m_Shape( 0 ), m_ConstraintGear( 0 )
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
	cpFloat ballRadius = 2.0;

	int linkfrom_pointfrom_x = getLinkFrom()->getPointFrom()->getX();
	int linkfrom_pointto_x = getLinkFrom()->getPointTo()->getX();

	int linkfrom_pointfrom_y = getLinkFrom()->getPointFrom()->getY();
	int linkfrom_pointto_y = getLinkFrom()->getPointTo()->getY();

	int linkto_pointfrom_x = getLinkTo()->getPointFrom()->getX();
	int linkto_pointto_x = getLinkTo()->getPointTo()->getX();

	int linkto_pointfrom_y = getLinkTo()->getPointFrom()->getY();
	int linkto_pointto_y = getLinkTo()->getPointTo()->getY();


	int linkfrom_katet_width = abs( linkfrom_pointfrom_x - linkfrom_pointto_x );
	int linkfrom_katet_height = abs( linkfrom_pointfrom_y - linkfrom_pointto_y );

	int linkfrom_vector_x = linkfrom_pointfrom_x - linkfrom_pointto_x;
	int linkfrom_vector_y = linkfrom_pointfrom_y - linkfrom_pointto_y;

	int linkto_vector_x = linkto_pointfrom_x - linkto_pointto_x;
	int linkto_vector_y = linkto_pointfrom_y - linkto_pointto_y;

	int linkto_katet_width = abs( linkto_pointfrom_x - linkto_pointto_x );
	int linkto_katet_height = abs( linkto_pointfrom_y - linkto_pointto_y );

	int linkfrom_length = sqrt( linkfrom_katet_width * linkfrom_katet_width + linkfrom_katet_height * linkfrom_katet_height );
	int linkto_length   = sqrt( linkto_katet_width   * linkto_katet_width   + linkto_katet_height   * linkto_katet_height );

	double tg = (double)( linkfrom_length - linkto_length ) / (double)( 1.0 + linkfrom_length * linkto_length );

	double cos = ( linkfrom_vector_x * linkto_vector_x + linkfrom_vector_y * linkto_vector_y )
			/
		 ( sqrt( linkfrom_vector_x * linkfrom_vector_x + linkfrom_vector_y * linkfrom_vector_y ) *
		   sqrt( linkto_vector_x * linkto_vector_x + linkto_vector_y * linkto_vector_y )
		 );

	double angle_from_tg = atan( tg );
	double angle_from_cos = acos( cos );

	int angle_tg_int = angle_from_tg / M_PI * 180;
	int angle_cos_int = angle_from_cos / M_PI * 180;

	int a = 0;
	a++;

	const GeometryLinkDynamic * linkFrom = getDynamicLinkFrom();
	const GeometryLinkDynamic * linkTo = getDynamicLinkTo();

	cpBody * bodyFrom = linkFrom->getBody();
	cpBody * bodyTo = linkTo->getBody();

	m_ConstraintGear = cpSpaceAddConstraint( m_Space, cpGearJointNew( bodyFrom, bodyTo, angle_from_cos, 1.0f ) );
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










