/*
 * DynamicSpringGetCrosslinkPredicate.h
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GeometrySpringGetShortestLinkPredicate_H_
#define PREDICATES_GeometrySpringGetShortestLinkPredicate_H_

#include "GeometrySpring.h"
#include "GeometryPoint.h"

class GeometrySpringGetShortestLinkPredicate
{
public:
	GeometrySpringGetShortestLinkPredicate( const GeometrySpring * geometrySpring );
	virtual ~GeometrySpringGetShortestLinkPredicate();

	const GeometryLink * operator()();

private:

	const GeometrySpring * m_GeometrySpring;

};

#endif /* PREDICATES_GeometrySpringGetShortestLinkPredicate_H_ */
