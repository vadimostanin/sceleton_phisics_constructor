/*
 * GeometryLinkGetAbsoluteAnglePredicate.h
 *
 *  Created on: 17 апр. 2015
 *      Author: vadim
 */

#ifndef PREDICATES_GeometryLinkGetAbsoluteAnglePredicate_H_
#define PREDICATES_GeometryLinkGetAbsoluteAnglePredicate_H_

#include "GeometryLink.h"

class GeometryLinkGetAbsoluteAnglePredicate
{
public:
	GeometryLinkGetAbsoluteAnglePredicate( const GeometryLink * link );
	GeometryLinkGetAbsoluteAnglePredicate( int link1X1, int link1Y1, int link1X2, int link1Y2 );
	virtual ~GeometryLinkGetAbsoluteAnglePredicate();

	int operator()();

private:

	const int m_linkX1;
	const int m_linkY1;

	const int m_linkX2;
	const int m_linkY2;

};

#endif /* PREDICATES_GeometryLinkGetAbsoluteAnglePredicate_H_ */
