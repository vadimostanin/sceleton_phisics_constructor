/*
 * GeometrySpring.cpp
 *
 *  Created on: Mar 26, 2015
 *      Author: vostanin
 */

#include "GeometrySpring.h"
#include <stdlib.h>
#include <sstream>
using namespace std;

GeometrySpring::GeometrySpring() : m_Id( rand() ), m_IsForward( true )
{
}

GeometrySpring::GeometrySpring( const GeometryLink * linkFrom, const GeometryLink * linkTo ) : m_Id( rand() ), m_IsForward( true )
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
	setIsForward( src.getIsForward() );

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

void GeometrySpring::setIsForward( bool isForward )
{
	m_IsForward = isForward;
}

bool GeometrySpring::getIsForward() const
{
	return m_IsForward;
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
	GeometrySpring * newSpring = new GeometrySpring;

	newSpring->setLinkFrom( this->getLinkFrom() );
	newSpring->setLinkTo( this->getLinkTo() );

	newSpring->setId( getId() );
	newSpring->setIsForward( getIsForward() );


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
	setIsForward( ((GeometrySpring &)src).getIsForward() );
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
	return GEOMETRYOBJECTCONSTRUCTING_COMPLETE;
}
