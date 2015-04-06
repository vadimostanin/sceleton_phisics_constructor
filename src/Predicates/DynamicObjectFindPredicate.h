/*
 * DynamicObjectFindPredicate.h
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#ifndef PREDICATES_DYNAMICOBJECTFINDPREDICATE_H_
#define PREDICATES_DYNAMICOBJECTFINDPREDICATE_H_

#include "IDynamicObject.h"

class DynamicObjectFindPredicate
{
public:
	DynamicObjectFindPredicate( const IDynamicObject * object );
	virtual ~DynamicObjectFindPredicate();

	bool operator()( const IDynamicObject * src );

private:

	const IDynamicObject * m_OriginObject;

};

#endif /* PREDICATES_DYNAMICOBJECTFINDPREDICATE_H_ */
