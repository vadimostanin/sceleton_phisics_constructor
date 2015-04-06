/*
 * DynamicLinksPointFindPredicate.h
 *
 *  Created on: 5 . 2015
 *      Author: vadim
 */

#ifndef DYNAMICLINKSPOINTFINDPREDICATE_H_
#define DYNAMICLINKSPOINTFINDPREDICATE_H_

#include "IDynamicObject.h"
#include "GeometryLinkDynamic.h"

class DynamicLinksPointFindPredicate
{
public:
	DynamicLinksPointFindPredicate( GeometryLinkDynamic & dynamicLink, bool find_point_from );
	virtual ~DynamicLinksPointFindPredicate();

	bool operator ()( const IDynamicObject * dynamicObject );

private:

	GeometryLinkDynamic & m_DynamicLink;
	bool m_FindPointFrom;

};

#endif /* DYNAMICLINKSPOINTFINDPREDICATE_H_ */
