/*
 * GeometryObjectFindPredicate.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTFINDPREDICATE_H_
#define GEOMETRYOBJECTFINDPREDICATE_H_

#include "IGeometryObject.h"

class GeometryObjectFindPredicate
{
public:
	GeometryObjectFindPredicate( IGeometryObject * origin );
	~GeometryObjectFindPredicate();
	bool operator()( IGeometryObject * object );
private:
	IGeometryObject * m_Origin;
};

#endif /* GEOMETRYOBJECTFINDPREDICATE_H_ */
