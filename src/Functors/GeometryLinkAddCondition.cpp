/*
 * GeometryLinkAddCondition.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: vostanin
 */

#include "GeometryLinkAddCondition.h"

GeometryLinkAddCondition::GeometryLinkAddCondition( const GeometryLink * origin ) : m_Origin( origin )
{
}

GeometryLinkAddCondition::~GeometryLinkAddCondition()
{
}

bool GeometryLinkAddCondition::operator()()
{
	if( m_Origin->getPointFrom() == m_Origin->getPointTo() )
	{
		return false;
	}
	return true;
}
















