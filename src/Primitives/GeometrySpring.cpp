/*
 * GeometrySpring.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "GeometrySpring.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLinksAngleGetPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

GeometrySpring::GeometrySpring() : m_Id( rand() ), m_IsClosedPath( true ), m_State( GEOMETRYOBJECTCONSTRUCTING_NONE )
{
	memset( m_geometryLinks, 0, sizeof( m_geometryLinks ) );
}

GeometrySpring::GeometrySpring( const GeometryLink * linkFrom, const GeometryLink * linkTo ) : m_Id( rand() ), m_IsClosedPath( true ), m_State( GEOMETRYOBJECTCONSTRUCTING_NONE )
{
	m_geometryLinks[0] = linkFrom;
	m_geometryLinks[1] = linkTo;
}

GeometrySpring::~GeometrySpring()
{
}

GeometrySpring & GeometrySpring::operator = ( const GeometrySpring & src )
{
	if( *this == src )
	{
		return *this;
	}
	const GeometryLink * link = src.getLinkFrom();
	setLinkFrom( link );
	setLinkTo( src.getLinkTo() );
	setIsClosedPath( src.getIsClosedPath() );

	return *this;
}

bool GeometrySpring::operator == ( const GeometrySpring & src ) const
{
	if( getLinkFrom() != src.getLinkFrom() )
	{
		return false;
	}
	if( getLinkTo() != src.getLinkTo() )
	{
		return false;
	}
	return true;
}

bool GeometrySpring::operator != ( const GeometrySpring & src ) const
{
	if( *this == src )
	{
		return false;
	}
	return true;
}

const GeometryLink * GeometrySpring::getLinkFrom() const
{
	return m_geometryLinks[0];
}

const GeometryLink * GeometrySpring::getLinkTo() const
{
	return m_geometryLinks[1];
}

//void GeometrySpring::setIsClosedPath( int x, int y )
//{
//	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( this );
//	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
//	GeometrySpringGetShortestLinkPredicate getShortesLink( this );
//	const GeometryLink * shorteslink = getShortesLink();
//
//	int crosslink_x = crosslinkPoint->getX();
//	int crosslink_y = crosslinkPoint->getY();
//
//	float degree = M_PI / 180.0;
//
//	GeometryPoint pointX0Y0( crosslink_x, crosslink_y );
//	GeometryPoint pointX0YN( crosslink_x + shorteslink->getWidth(), crosslink_y );
//	GeometryLink linkY0( &pointX0Y0, &pointX0YN );
//
//	GeometryLinksAngleGetPredicate getAngleLinkFrom( getLinkFrom(), &linkY0 );
//	GeometryLinksAngleGetPredicate getAngleLinkTo( getLinkFrom(), &linkY0 );
//
//	float linkFromAngle = getAngleLinkFrom();
//	float linkToAngle = getAngleLinkTo();
//
//	int linkFromAngleInt = linkFromAngle / M_PI * 180.0;
//	int linkToAngleInt = linkToAngle / M_PI * 180.0;

//}

void GeometrySpring::setIsClosedPath( int x, int y )
{
	int linkFromAbsoluteAngle = getLinkFrom()->getAngle();
	int linkToAbsoluteAngle = getLinkTo()->getAngle();

	int minAngle = min( linkFromAbsoluteAngle, linkToAbsoluteAngle );
	int maxAngle = max( linkFromAbsoluteAngle, linkToAbsoluteAngle );

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( this );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();

	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( crosslinkPoint->getX(), crosslinkPoint->getY(), x, y );
	int currentAbsoluteAngle = getCurrentPointAbsoluteAngle();
	if( currentAbsoluteAngle > minAngle && currentAbsoluteAngle < maxAngle )
	{
		setIsClosedPath( true );
		cout << "true" << endl << flush;
	}
	else
	{
		setIsClosedPath( false );
		cout << "false" << endl << flush;
	}
}

void GeometrySpring::setIsClosedPath( bool isClosedPath )
{
	m_IsClosedPath = isClosedPath;
}

bool GeometrySpring::getIsClosedPath() const
{
	return m_IsClosedPath;
}

void GeometrySpring::setLinkFrom( const GeometryLink * linkFrom )
{
	m_geometryLinks[0] = linkFrom;
}

void GeometrySpring::setLinkTo( const GeometryLink * linkTo )
{
	m_geometryLinks[1] = linkTo;
}

int GeometrySpring::getId() const
{
	return m_Id;
}

void GeometrySpring::setId( int id)
{
	m_Id = id;
}

IGeometryObject * GeometrySpring::clone()
{
	GeometrySpring * newSpring = new GeometrySpring( getLinkFrom(), getLinkTo() );
	newSpring->setId( getId() );
	newSpring->setIsClosedPath( getIsClosedPath() );


	return newSpring;
}

string GeometrySpring::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << getLinkFrom()->getId() << " " << getLinkTo()->getId() << flush;

	return stream.str();
}

IGeometryObject & GeometrySpring::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_SPRING )
	{
		return *this;
	}

	const GeometryLink * link = ((GeometrySpring &)src).getLinkFrom();
	setLinkFrom( link );
	setLinkTo( ((GeometrySpring &)src).getLinkTo() );
	setIsClosedPath( ((GeometrySpring &)src).getIsClosedPath() );
	setId( ((GeometrySpring &)src).getId() );

	return *this;
}

bool GeometrySpring::isValid()
{
    if ( getLinkFrom()->getType() == GEOMETRYOBJECT_DUMMY )
    {
        return false;
    }
    if ( getLinkTo()->getType() == GEOMETRYOBJECT_DUMMY )
    {
        return false;
    }
	return true;
}

GeometryObjectsTypes GeometrySpring::getType() const
{
	return GEOMETRYOBJECT_SPRING;
}

GeometryObjectsConstructiongStates GeometrySpring::getConstructingState()
{
	return m_State;
}

void GeometrySpring::setConstructingState( GeometryObjectsConstructiongStates state )
{
	m_State = state;
}
