/*
 * DynamicSpringGetCrosslinkPredicate.h
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_DynamicSpringGetCrosslinkPredicate_H_
#define PREDICATES_DynamicSpringGetCrosslinkPredicate_H_

#include "GeometrySpringDynamic.h"
#include "GeometryPointDynamic.h"

class DynamicSpringGetCrosslinkPredicate
{
public:
	DynamicSpringGetCrosslinkPredicate( GeometrySpringDynamic * dynamicSpring );
	virtual ~DynamicSpringGetCrosslinkPredicate();

	const GeometryPointDynamic * operator()();

private:

	 GeometrySpringDynamic * m_DynamicSpring;

};

#endif /* PREDICATES_DynamicSpringGetCrosslinkPredicate_H_ */
