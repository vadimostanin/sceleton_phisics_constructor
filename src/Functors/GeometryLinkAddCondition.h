/*
 * GeometryObjectAddCondition.h
 *
 *  Created on: Apr 14, 2015
 *      Author: vostanin
 */

#ifndef PREDICATES_GEOMETRYLINKADDCONDITION_H_
#define PREDICATES_GEOMETRYLINKADDCONDITION_H_

#include "GeometryLink.h"

class GeometryLinkAddCondition
{
public:
	GeometryLinkAddCondition( const GeometryLink * origin );
	virtual ~GeometryLinkAddCondition();

	bool operator()();

private:

	const GeometryLink * m_Origin;

};

#endif /* PREDICATES_GEOMETRYLINKADDCONDITION_H_ */
