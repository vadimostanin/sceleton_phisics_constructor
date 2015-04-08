/*
 * DynamicLinksPointFindPredicate.cpp
 *
 *  Created on: 5 ������������������. 2015
 *      Author: vadim
 */

#include "DynamicSpringsLinkFindPredicate.h"
#include "GeometryLink.h"

DynamicSpringsLinkFindPredicate::DynamicSpringsLinkFindPredicate( GeometrySpringDynamic & dynamicSpring, bool findLinkFrom ) :
		m_DynamicSpring( dynamicSpring ), m_FindLinkFrom( findLinkFrom )
{
}

DynamicSpringsLinkFindPredicate::~DynamicSpringsLinkFindPredicate()
{
}

bool DynamicSpringsLinkFindPredicate::operator ()( const IDynamicObject * dynamicObject )
{
	const IGeometryObject & iterObject = dynamicObject->getGeometryObject();
	if( iterObject.getType() != GEOMETRYOBJECT_LINK )
	{
		return false;
	}
	const IGeometryObject * originObject = NULL;
	if( true == m_FindLinkFrom )
	{
		originObject = ((GeometrySpring &)m_DynamicSpring.getGeometryObject()).getLinkFrom();
	}
	else
	{
		originObject = ((GeometrySpring &)m_DynamicSpring.getGeometryObject()).getLinkTo();
	}

	if( originObject->getId() == iterObject.getId() )
	{
		return true;
	}
	return false;
}















