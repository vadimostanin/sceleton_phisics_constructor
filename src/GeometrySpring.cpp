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
	// TODO Auto-generated constructor stub

}

GeometrySpring::~GeometrySpring()
{
	// TODO Auto-generated destructor stub
}

GeometrySpring & GeometrySpring::operator = ( const GeometrySpring & src )
{

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

const GeometryLink & GeometrySpring::getLinkFrom() const
{
	return m_geometryLinks[0];
}

const GeometryLink & GeometrySpring::getLinkTo() const
{
	return m_geometryLinks[1];
}

const int GeometrySpring::getLength() const
{
	return m_Length;
}

void GeometrySpring::setLinkFrom( GeometryLink & linkFrom )
{
	m_geometryLinks[0] = linkFrom;
}

void GeometrySpring::setLinkTo( GeometryLink & linkTo )
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
	GeometrySpring * newPoint = new GeometrySpring;

	newPoint->m_Id = m_Id;
	newPoint->m_Length = m_Length;


	return newPoint;
}

string GeometrySpring::toString()
{
	stringstream stream;

	return stream.str();
}

IGeometryObject & GeometrySpring::operator = ( IGeometryObject & src )
{
	if( src.getType() != GEOMETRYOBJECT_SPRING )
	{
		return *this;
	}

	return *this;
}

GeometryObjectsTypes GeometrySpring::getType() const
{
	return GEOMETRYOBJECT_SPRING;
}
