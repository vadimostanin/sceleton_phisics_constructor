/*
 * DynamicLinksPointFindPredicate.h
 *
 *  Created on: 5 . 2015
 *      Author: vadim
 */

#ifndef DYNAMICSPRINGSLINKFINDPREDICATE_H_
#define DYNAMICSPRINGSLINKFINDPREDICATE_H_

#include "IDynamicObject.h"
#include "GeometrySpringDynamic.h"

class DynamicSpringsLinkFindPredicate
{
public:
	DynamicSpringsLinkFindPredicate( GeometrySpringDynamic & dynamicSpring, bool findLinkFrom );
	virtual ~DynamicSpringsLinkFindPredicate();

	bool operator ()( const IDynamicObject * dynamicObject );

private:

	GeometrySpringDynamic & m_DynamicSpring;
	bool m_FindLinkFrom;

};

#endif /* DYNAMICSPRINGSLINKFINDPREDICATE_H_ */
