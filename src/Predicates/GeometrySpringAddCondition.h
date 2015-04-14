/*
 * GeometrySpringAddCondition.h
 *
 *  Created on: Apr 14, 2015
 *      Author: vostanin
 */

#ifndef PREDICATES_GEOMETRYSPRINGADDCONDITION_H_
#define PREDICATES_GEOMETRYSPRINGADDCONDITION_H_

#include "GeometrySpring.h"

class GeometrySpringAddCondition
{
public:
	GeometrySpringAddCondition( const GeometrySpring * origin );
	virtual ~GeometrySpringAddCondition();

	bool operator()();

private:

	const GeometrySpring * m_Origin;

};

#endif /* PREDICATES_GEOMETRYSPRINGADDCONDITION_H_ */
