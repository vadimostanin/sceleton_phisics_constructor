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

GeometrySpring::GeometrySpring() : m_Id( rand() ), m_Length( 0 )
{
}

GeometrySpring::GeometrySpring( const GeometryLink * linkFrom, const GeometryLink * linkTo ) : m_Id( rand() ), m_Length( 0 )
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
	const GeometryLink & link = src.getLinkFrom();
	setLinkFrom( link );
	setLinkTo( src.getLinkTo() );
	m_Length = src.getLength();

	return *this;
}

bool GeometrySpring::operator == ( const GeometrySpring & src ) const
{
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

const int GeometrySpring::getLength() const
{
	return m_Length;
}

void GeometrySpring::setLinkFrom( const GeometryLink * linkFrom )
{
	m_geometryLinks[0] = linkFrom;
}

void GeometrySpring::setLinkTo( const GeometryLink * linkTo )
{
	m_geometryLinks[1] = linkTo;
}

void GeometrySpring::setLength( int length )
{
	m_Length = length;
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

	newSpring->m_Id = m_Id;
	newSpring->m_Length = m_Length;


	return newSpring;
}

string GeometrySpring::toString()
{
	stringstream stream;

	stream << getType() << " " << getId() << " " << getLinkFrom().getId() << " " << getLinkTo().getId() << flush;

	return stream.str();
}

IGeometryObject & GeometrySpring::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_SPRING )
	{
		return *this;
	}

	const GeometryLink & link = ((GeometrySpring &)src).getLinkFrom();
	setLinkFrom( link );
	setLinkTo( ((GeometrySpring &)src).getLinkTo() );
	m_Length = ((GeometrySpring &)src).getLength();
	m_Id = ((GeometrySpring &)src).getId();

	return *this;
}

GeometryObjectsTypes GeometrySpring::getType() const
{
	return GEOMETRYOBJECT_SPRING;
}
