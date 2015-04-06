/*
 * DynamicLinksPointFindPredicate.cpp
 *
 *  Created on: 5 ������. 2015
 *      Author: vadim
 */

#include "DynamicLinksPointFindPredicate.h"
#include "GeometryLink.h"

DynamicLinksPointFindPredicate::DynamicLinksPointFindPredicate( GeometryLinkDynamic & dynamicLink, bool findPointFrom ) :
								m_DynamicLink( dynamicLink ), m_FindPointFrom( findPointFrom )
{
}

DynamicLinksPointFindPredicate::~DynamicLinksPointFindPredicate()
{
}

bool DynamicLinksPointFindPredicate::operator ()( const IDynamicObject * dynamicObject )
{
	const IGeometryObject & iterObject = dynamicObject->getGeometryObject();
	if( iterObject.getType() != GEOMETRYOBJECT_POINT )
	{
		return false;
	}
	const IGeometryObject * originObject = NULL;
	if( true == m_FindPointFrom )
	{
		originObject = ((GeometryLink &)m_DynamicLink.getGeometryObject()).getPointFrom();
	}
	else
	{
		originObject = ((GeometryLink &)m_DynamicLink.getGeometryObject()).getPointTo();
	}

	if( originObject->getId() == iterObject.getId() )
	{
		return true;
	}
	return false;
}















