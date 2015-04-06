/*
 * GeometryObjectFindPredicate.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#include "GeometryObjectFindPredicate.h"

GeometryObjectFindPredicate::GeometryObjectFindPredicate( IGeometryObject * origin ) : m_Origin( origin )
{

}

GeometryObjectFindPredicate::~GeometryObjectFindPredicate()
{
	;
}

bool GeometryObjectFindPredicate::operator()( IGeometryObject * object )
{
	if( object->getId() == m_Origin->getId() )
	{
		return true;
	}
	return false;
}

