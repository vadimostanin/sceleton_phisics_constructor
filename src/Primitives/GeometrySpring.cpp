/*
 * GeometrySpring.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "GeometrySpring.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
#include "IsAngleInShortPathBetweenTwo.h"
#include "GeometrySpringGetAngles.h"
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

void GeometrySpring::setIsClosedPath( int x, int y )
{
	if( getConstructingState() != GEOMETRYOBJECTCONSTRUCTING_INPROGRESS )
	{
		return;
	}
	GeometrySpringGetAngles getAngles( this );
	int linkFromAbsoluteAngle = getAngles.getLinkFromAngle();
	int linkToAbsoluteAngle = getAngles.getLinkToAngle();

	GeometrySpringGetCrosslinkPredicate getCrosslinkPoint( this );
	const GeometryPoint * crosslinkPoint = getCrosslinkPoint();
//cout << "cross=" << crosslinkPoint->getX() << "x" << crosslinkPoint->getY() << endl << flush;
	GeometryLinkGetAbsoluteAnglePredicate getCurrentPointAbsoluteAngle( crosslinkPoint->getX(), crosslinkPoint->getY(), x, y );
	int currentAbsoluteAngle = getCurrentPointAbsoluteAngle();
	IsAngleInShortPathBetweenTwo isAngleBetween( linkFromAbsoluteAngle, linkToAbsoluteAngle, currentAbsoluteAngle );
	if( true == isAngleBetween() )
	{
		setIsClosedPath( true );
		cout << "true=" << "curr=" << currentAbsoluteAngle << "; from=" << linkFromAbsoluteAngle << "; to=" << linkToAbsoluteAngle << endl << flush;
	}
	else
	{
		setIsClosedPath( false );
		cout << "false=" << "curr=" << currentAbsoluteAngle << "; from=" << linkFromAbsoluteAngle << "; to=" << linkToAbsoluteAngle << endl << flush;
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

GeometryObjectsConstructiongStates GeometrySpring::getConstructingState() const
{
	return m_State;
}

void GeometrySpring::setConstructingState( GeometryObjectsConstructiongStates state )
{
	m_State = state;
}
