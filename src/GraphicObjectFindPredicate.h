/*
 * GeometryObjectFindPredicate.h
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTFINDPREDICATE_H_
#define GEOMETRYOBJECTFINDPREDICATE_H_

#include "IGraphicObject.h"

class GraphicObjectFindPredicate
{
public:
	GraphicObjectFindPredicate( IGraphicObject * origin );
	~GraphicObjectFindPredicate();
	bool operator()( IGraphicObject * object );
private:
	IGraphicObject * m_Origin;
};

#endif /* GEOMETRYOBJECTFINDPREDICATE_H_ */
