/*
 * GeometryObjectFindPredicate.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#include "GraphicObjectFindPredicate.h"

GraphicObjectFindPredicate::GraphicObjectFindPredicate( IGraphicObject * origin ) : m_Origin( origin )
{

}

GraphicObjectFindPredicate::~GraphicObjectFindPredicate()
{
	;
}

bool GraphicObjectFindPredicate::operator()( IGraphicObject * object )
{
	if( object->getGeometryObject().getId() == m_Origin->getGeometryObject().getId() )
	{
		return true;
	}
	return false;
}

