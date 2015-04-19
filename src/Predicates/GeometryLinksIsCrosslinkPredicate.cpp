/*
 * DynamicSpringGetCrosslinkPredicate.cpp
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#include "GeometryLinksIsCrosslinkPredicate.h"
#include "GeometryLink.h"

GeometryLinksIsCrosslinkPredicate::GeometryLinksIsCrosslinkPredicate( const GeometryLink * link1, const GeometryLink * link2 ) :
	m_Link1( link1 ), m_Link2( link2 )
{
}

GeometryLinksIsCrosslinkPredicate::~GeometryLinksIsCrosslinkPredicate()
{
}

bool GeometryLinksIsCrosslinkPredicate::operator()()
{
	if( m_Link1->getPointFrom() == m_Link2->getPointFrom() )
	{
		return true;
	}
	else if( m_Link1->getPointTo() == m_Link2->getPointTo() )
	{
		return true;
	}
	else if( m_Link1->getPointFrom() == m_Link2->getPointTo() )
	{
		return true;
	}
	else if( m_Link1->getPointTo() == m_Link2->getPointFrom() )
	{
		return true;
	}

	return false;
}

















