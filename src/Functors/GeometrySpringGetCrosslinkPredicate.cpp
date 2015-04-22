/*
 * DynamicSpringGetCrosslinkPredicate.cpp
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#include "GeometrySpringGetCrosslinkPredicate.h"
#include "GeometryLink.h"

GeometrySpringGetCrosslinkPredicate::GeometrySpringGetCrosslinkPredicate( const GeometrySpring * geometrySpring ) : m_GeometrySpring( geometrySpring )
{
}

GeometrySpringGetCrosslinkPredicate::~GeometrySpringGetCrosslinkPredicate()
{
}

const GeometryPoint * GeometrySpringGetCrosslinkPredicate::operator()()
{
	const GeometryLink * linkFrom = m_GeometrySpring->getLinkFrom();
	const GeometryLink * linkTo = m_GeometrySpring->getLinkTo();

	const GeometryPoint * result = NULL;

	if( linkFrom->getPointFrom() == linkTo->getPointFrom() )
	{
		result = linkFrom->getPointFrom();
	}
	else if( linkFrom->getPointTo() == linkTo->getPointTo() )
	{
		result = linkFrom->getPointTo();
	}
	else if( linkFrom->getPointFrom() == linkTo->getPointTo() )
	{
		result = linkFrom->getPointTo();
	}
	else if( linkFrom->getPointTo() == linkTo->getPointFrom() )
	{
		result = linkFrom->getPointTo();
	}

	return result;
}

















