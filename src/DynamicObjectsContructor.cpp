/*
 * DynamicObjectsContructor.cpp
 *
 *  Created on: 5 апр. 2015
 *      Author: vadim
 */

#include "DynamicObjectsContructor.h"
#include "DynamicObjectFactory.h"

DynamicObjectsContructor::DynamicObjectsContructor( int CanvasWidth, int CanvasHeight ) : m_CanvasWidth( CanvasWidth ), m_CanvasHeight( CanvasHeight )
{
}

DynamicObjectsContructor::~DynamicObjectsContructor()
{
}

void DynamicObjectsContructor::convertToDynamic( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects )
{
	DynamicObjectFactory::getInstance().setCanvasWidth( m_CanvasWidth );
	DynamicObjectFactory::getInstance().setCanvasHeight( m_CanvasHeight );

	DynamicObjectFactory::getInstance().init();

	vector<IGeometryObject *>::iterator begin = geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		IDynamicObject * dynamicObject = (GeometryPointDynamic *)DynamicObjectFactory::getInstance().createDynamicObject( (*iter) );

		dynamicObjects.push_back( dynamicObject );
	}
}

void DynamicObjectsContructor::setCanvasWidth( int width )
{
	m_CanvasWidth = width;
}

void DynamicObjectsContructor::setCanvasHeight( int height )
{
	m_CanvasHeight = height;
}













