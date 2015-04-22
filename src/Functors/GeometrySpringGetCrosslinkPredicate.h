/*
 * DynamicSpringGetCrosslinkPredicate.h
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GeometrySpringGetCrosslinkPredicate_H_
#define PREDICATES_GeometrySpringGetCrosslinkPredicate_H_

#include "GeometrySpring.h"
#include "GeometryPoint.h"

class GeometrySpringGetCrosslinkPredicate
{
public:
	GeometrySpringGetCrosslinkPredicate( const GeometrySpring * geometrySpring );
	virtual ~GeometrySpringGetCrosslinkPredicate();

	const GeometryPoint * operator()();

private:

	const GeometrySpring * m_GeometrySpring;

};

#endif /* PREDICATES_GeometrySpringGetCrosslinkPredicate_H_ */
