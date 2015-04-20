/*
 * DynamicSpringGetCrosslinkPredicate.cpp
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#include "DynamicSpringGetCrosslinkPredicate.h"
#include "GeometryLink.h"

DynamicSpringGetCrosslinkPredicate::DynamicSpringGetCrosslinkPredicate( GeometrySpringDynamic * dynamicSpring ) : m_DynamicSpring( dynamicSpring )
{
}

DynamicSpringGetCrosslinkPredicate::~DynamicSpringGetCrosslinkPredicate()
{
}

const GeometryPointDynamic * DynamicSpringGetCrosslinkPredicate::operator()()
{
	const GeometryLinkDynamic * linkFrom = m_DynamicSpring->getDynamicLinkFrom();
	const GeometryLinkDynamic * linkTo = m_DynamicSpring->getDynamicLinkTo();

	const GeometryPointDynamic * result = NULL;

	if( linkFrom->getDynamicPointFrom() == linkTo->getDynamicPointFrom() )
	{
		result = linkFrom->getDynamicPointFrom();
	}
	else if( linkFrom->getDynamicPointTo() == linkTo->getDynamicPointTo() )
	{
		result = linkFrom->getDynamicPointTo();
	}
	else if( linkFrom->getDynamicPointFrom() == linkTo->getDynamicPointTo() )
	{
		result = linkFrom->getDynamicPointTo();
	}
	else if( linkFrom->getDynamicPointTo() == linkTo->getDynamicPointFrom() )
	{
		result = linkFrom->getDynamicPointTo();
	}

	return result;
}

















