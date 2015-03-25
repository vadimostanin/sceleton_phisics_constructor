/*
 * GeometryObjectFindPredicate.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: vostanin
 */

#include "GraphicObjectFindPredicate.h"
#include <iostream>
using namespace std;

GraphicObjectFindPredicate::GraphicObjectFindPredicate( IGraphicObject * origin ) : m_Origin( origin )
{
//	cout << "Origin iter:" << m_Origin->getGeometryObject().toString() << endl << flush;
}

GraphicObjectFindPredicate::~GraphicObjectFindPredicate()
{
	;
}

bool GraphicObjectFindPredicate::operator()( IGraphicObject * object )
{
//	cout << "search iter:" << object->getGeometryObject().toString() << endl << flush;
	if( object->getGeometryObject().getId() == m_Origin->getGeometryObject().getId() )
	{
		return true;
	}
	return false;
}

