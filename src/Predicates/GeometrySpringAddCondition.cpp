/*
 * GeometryLinkAddCondition.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: vostanin
 */

#include "GeometrySpringAddCondition.h"

GeometrySpringAddCondition::GeometrySpringAddCondition( const GeometrySpring * origin ) : m_Origin( origin )
{
}

GeometrySpringAddCondition::~GeometrySpringAddCondition()
{
}

bool GeometrySpringAddCondition::operator()()
{
	if( m_Origin->getLinkFrom() == m_Origin->getLinkTo() )
	{
		return false;
	}

	if( m_Origin->getLinkFrom()->getPointFrom() == m_Origin->getLinkTo()->getPointFrom() )
	{
		return true;
	}
	else if( m_Origin->getLinkFrom()->getPointTo() == m_Origin->getLinkTo()->getPointTo() )
	{
		return true;
	}
	else if( m_Origin->getLinkFrom()->getPointFrom() == m_Origin->getLinkTo()->getPointTo() )
	{
		return true;
	}
	else if( m_Origin->getLinkFrom()->getPointTo() == m_Origin->getLinkTo()->getPointFrom() )
	{
		return true;
	}

	return false;
}
















