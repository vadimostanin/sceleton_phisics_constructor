/*
 * DynamicObjectsContructor.cpp
 *
 *  Created on: 5 апр. 2015
 *      Author: vadim
 */

#include "DynamicObjectsContructor.h"
#include "DynamicObjectFactory.h"
#include "DynamicLinksPointFindPredicate.h"
#include <algorithm>
using namespace std;

DynamicObjectsContructor::DynamicObjectsContructor( int CanvasWidth, int CanvasHeight ) : m_CanvasWidth( CanvasWidth ), m_CanvasHeight( CanvasHeight )
{
}

DynamicObjectsContructor::~DynamicObjectsContructor()
{
}

void DynamicObjectsContructor::convert( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects )
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

void DynamicObjectsContructor::convertSmart( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects )
{
	DynamicObjectFactory::getInstance().setCanvasWidth( m_CanvasWidth );
	DynamicObjectFactory::getInstance().setCanvasHeight( m_CanvasHeight );

	DynamicObjectFactory::getInstance().init();

	vector<IGeometryObject *>::iterator geometryBegin = geometryObjects.begin();
	vector<IGeometryObject *>::iterator geometryEnd = geometryObjects.end();
	vector<IGeometryObject *>::iterator geometryIter = geometryBegin;

	for(  ; geometryIter != geometryEnd ; geometryIter ++ )
	{
		IDynamicObject * dynamicObject = (GeometryPointDynamic *)DynamicObjectFactory::getInstance().createDynamicObject( (* geometryIter) );
		dynamicObjects.push_back( dynamicObject );
	}

	vector<IDynamicObject *>::iterator dynamicBegin = dynamicObjects.begin();
	vector<IDynamicObject *>::iterator dynamicEnd = dynamicObjects.end();
	vector<IDynamicObject *>::iterator dynamicIter = dynamicBegin;

	vector<IDynamicObject *>::iterator foundPointFromIter;
	vector<IDynamicObject *>::iterator foundPointToIter;

	for(  ; dynamicIter != dynamicEnd ; dynamicIter ++ )
	{
		if( (* dynamicIter)->getGeometryObject().getType() != GEOMETRYOBJECT_LINK )
		{
			continue;
		}

		{
			DynamicLinksPointFindPredicate predicate( *(GeometryLinkDynamic *)(* dynamicIter), true );
			foundPointFromIter = find_if( dynamicBegin, dynamicEnd, predicate );
		}
		{
			DynamicLinksPointFindPredicate predicate( *(GeometryLinkDynamic *)(* dynamicIter), false );
			foundPointToIter = find_if( dynamicBegin, dynamicEnd, predicate );
		}
		if( foundPointFromIter == dynamicEnd || foundPointToIter == dynamicEnd )
		{
			continue;
		}
		((GeometryLinkDynamic *)(* dynamicIter))->setDynamicPointFrom( (GeometryPointDynamic *)(* foundPointFromIter) );
		((GeometryLinkDynamic *)(* dynamicIter))->setDynamicPointTo( (GeometryPointDynamic *)(* foundPointToIter) );
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













