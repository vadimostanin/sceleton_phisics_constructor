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
	GeometryLinksAngleGetPredicate( int link1X1, int link1Y1, int link1X2, int link1Y2, int link2X1, int link2Y1, int link2X2, int link2Y2 );
	virtual ~GeometryLinksAngleGetPredicate();

	float operator()();

private:

	const int m_link1X1;
	const int m_link1Y1;

	const int m_link1X2;
	const int m_link1Y2;

	const int m_link2X1;
	const int m_link2Y1;

	const int m_link2X2;
	const int m_link2Y2;

};

#endif /* PREDICATES_GEOMETRYLINKSANGLEGETPREDICATE_H_ */
