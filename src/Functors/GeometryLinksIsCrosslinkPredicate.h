/*
 * DynamicSpringGetCrosslinkPredicate.h
 *
 *  Created on: 15 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GeometrySpringGetCrosslinkPredicate_H_
#define PREDICATES_GeometrySpringGetCrosslinkPredicate_H_

#include "GeometryLink.h"

class GeometryLinksIsCrosslinkPredicate
{
public:
	GeometryLinksIsCrosslinkPredicate( const GeometryLink * link1, const GeometryLink * link2 );
	virtual ~GeometryLinksIsCrosslinkPredicate();

	bool operator()();

private:

	const GeometryLink * m_Link1;
	const GeometryLink * m_Link2;

};

#endif /* PREDICATES_GeometrySpringGetCrosslinkPredicate_H_ */
