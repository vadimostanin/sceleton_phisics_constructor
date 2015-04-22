/*
 * DynamicSpringGetCrosslinkPredicate.cpp
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#include "GeometrySpringGetShortestLinkPredicate.h"
#include "GeometryLink.h"
#include <cmath>

GeometrySpringGetShortestLinkPredicate::GeometrySpringGetShortestLinkPredicate( const GeometrySpring * geometrySpring ) : m_GeometrySpring( geometrySpring )
{
}

GeometrySpringGetShortestLinkPredicate::~GeometrySpringGetShortestLinkPredicate()
{
}

const GeometryLink * GeometrySpringGetShortestLinkPredicate::operator()()
{
	const GeometryLink * linkFrom = m_GeometrySpring->getLinkFrom();
	const GeometryLink * linkTo = m_GeometrySpring->getLinkTo();

	const GeometryLink * result = NULL;

	int linkfrom_width = linkFrom->getWidth();

	int linkto_width = linkTo->getWidth();

	if( linkto_width < linkfrom_width )
	{
		result = linkTo;
	}
	else
	{
		result = linkFrom;
	}

	return result;
}

















