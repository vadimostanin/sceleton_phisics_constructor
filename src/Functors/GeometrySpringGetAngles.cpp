/*
 * GeometrySpringGetAngles.cpp
 *
 *  Created on: 22 апр. 2015
 *      Author: vadim
 */

#include "GeometrySpringGetAngles.h"
#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"

GeometrySpringGetAngles::GeometrySpringGetAngles( const GeometrySpring * geometrySpring ) :
	m_GeometrySpring( geometrySpring ), m_CrossPoint( 0 )
{
	GeometrySpringGetCrosslinkPredicate getCrosspoint( m_GeometrySpring );
	m_CrossPoint = getCrosspoint();

}

GeometrySpringGetAngles::~GeometrySpringGetAngles()
{
}

bool GeometrySpringGetAngles::getIsValid() const
{
	return m_CrossPoint != NULL;
}

const GeometryPoint * GeometrySpringGetAngles::getCrospoint() const
{
	return m_CrossPoint;
}

const GeometryPoint * GeometrySpringGetAngles::getLinkFromAdjacentPoint() const
{
	const GeometryPoint * result = NULL;

	if( m_GeometrySpring->getLinkFrom()->getPointFrom() == getCrospoint() )
	{
		result = m_GeometrySpring->getLinkFrom()->getPointTo();
	}
	else
	{
		result = m_GeometrySpring->getLinkFrom()->getPointFrom();
	}

	return result;
}

const GeometryPoint * GeometrySpringGetAngles::getLinkToAdjacentPoint() const
{
	const GeometryPoint * result = NULL;

	if( m_GeometrySpring->getLinkTo()->getPointFrom() == getCrospoint() )
	{
		result = m_GeometrySpring->getLinkTo()->getPointTo();
	}
	else
	{
		result = m_GeometrySpring->getLinkTo()->getPointFrom();
	}

	return result;
}

int GeometrySpringGetAngles::getLinkFromAngle() const
{
	int linkX1 = getCrospoint()->getX();
	int linkY1 = getCrospoint()->getY();
	int linkX2 = getLinkFromAdjacentPoint()->getX();
	int linkY2 = getLinkFromAdjacentPoint()->getY();

	GeometryLinkGetAbsoluteAnglePredicate getLinkAbsoluteAngle( linkX1, linkY1, linkX2, linkY2 );
	return getLinkAbsoluteAngle();
}

int GeometrySpringGetAngles::getLinkToAngle() const
{
	int linkX1 = getCrospoint()->getX();
	int linkY1 = getCrospoint()->getY();
	int linkX2 = getLinkToAdjacentPoint()->getX();
	int linkY2 = getLinkToAdjacentPoint()->getY();

	GeometryLinkGetAbsoluteAnglePredicate getLinkAbsoluteAngle( linkX1, linkY1, linkX2, linkY2 );
	return getLinkAbsoluteAngle();
}








