/*
 * GeometryLinksAngleGetPredicate.h
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GEOMETRYLINKSANGLEGETPREDICATE_H_
#define PREDICATES_GEOMETRYLINKSANGLEGETPREDICATE_H_

#include "GeometryLink.h"

class GeometryLinksAngleGetPredicate
{
public:
	GeometryLinksAngleGetPredicate( const GeometryLink * link1, const GeometryLink * link2 );
	virtual ~GeometryLinksAngleGetPredicate();

	float operator()();

private:

	const GeometryLink * m_Link1;
	const GeometryLink * m_Link2;

};

#endif /* PREDICATES_GEOMETRYLINKSANGLEGETPREDICATE_H_ */
