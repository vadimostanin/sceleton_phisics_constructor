/*
 * DynamicObjectsContructor.cpp
 *
 *  Created on: 5 ������. 2015
 *      Author: vadim
 */

#include "DynamicObjectsContructor.h"
#include "DynamicObjectFactory.h"
#include "DynamicLinksPointFindPredicate.h"
#include "DynamicSpringsLinkFindPredicate.h"
#include <algorithm>
using namespace std;

DynamicObjectsContructor::DynamicObjectsContructor() : m_CanvasWidth( 0 ), m_CanvasHeight( 0 )
{
}

DynamicObjectsContructor::~DynamicObjectsContructor()
{
}

void DynamicObjectsContructor::convert( vector<IGeometryObject *> & geometryObjects, vector<IDynamicObject *> & dynamicObjects )
{
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

	vector<IGeometryObject *>::iterator geometryBegin = geometryObjects.begin();
	vector<IGeometryObject *>::iterator geometryEnd = geometryObjects.end();
	vector<IGeometryObject *>::iterator geometryIter = geometryBegin;

	for(  ; geometryIter != geometryEnd ; geometryIter ++ )
	{
		IDynamicObject * dynamicObject = (GeometryPointDynamic *)DynamicObjectFactory::getInstance().createDynamicObject( (* geometryIter) );
		if( 0 == dynamicObject )
		{
			continue;
		}
		dynamicObjects.push_back( dynamicObject );
	}

	vector<IDynamicObject *>::iterator dynamicBegin = dynamicObjects.begin();
	vector<IDynamicObject *>::iterator dynamicEnd = dynamicObjects.end();
	vector<IDynamicObject *>::iterator dynamicIter = dynamicBegin;

	vector<IDynamicObject *>::iterator foundPointFromIter;
	vector<IDynamicObject *>::iterator foundPointToIter;

	for(  ; dynamicIter != dynamicEnd ; dynamicIter ++ )
	{
		IDynamicObject * dynamic_ptr = (* dynamicIter);
		if( dynamic_ptr->getGeometryObject().getType() == GEOMETRYOBJECT_LINK )
		{
			{
				DynamicLinksPointFindPredicate predicate( *(GeometryLinkDynamic *)dynamic_ptr, true );
				foundPointFromIter = find_if( dynamicBegin, dynamicEnd, predicate );
			}
			{
				DynamicLinksPointFindPredicate predicate( *(GeometryLinkDynamic *)dynamic_ptr, false );
				foundPointToIter = find_if( dynamicBegin, dynamicEnd, predicate );
			}
			if( foundPointFromIter == dynamicEnd || foundPointToIter == dynamicEnd )
			{
				continue;
			}
			((GeometryLinkDynamic *)dynamic_ptr)->setDynamicPointFrom( (GeometryPointDynamic *)(* foundPointFromIter) );
			((GeometryLinkDynamic *)dynamic_ptr)->setDynamicPointTo( (GeometryPointDynamic *)(* foundPointToIter) );
		}
		else if( dynamic_ptr->getGeometryObject().getType() == GEOMETRYOBJECT_SPRING )
		{
			{
				DynamicSpringsLinkFindPredicate predicate( *(GeometrySpringDynamic *)dynamic_ptr, true );
				foundPointFromIter = find_if( dynamicBegin, dynamicEnd, predicate );
			}
			{
				DynamicSpringsLinkFindPredicate predicate( *(GeometrySpringDynamic *)dynamic_ptr, false );
				foundPointToIter = find_if( dynamicBegin, dynamicEnd, predicate );
			}
			if( foundPointFromIter == dynamicEnd || foundPointToIter == dynamicEnd )
			{
				continue;
			}
			((GeometrySpringDynamic *)dynamic_ptr)->setDynamicLinkFrom( (GeometryLinkDynamic *)(* foundPointFromIter) );
			((GeometrySpringDynamic *)dynamic_ptr)->setDynamicLinkTo( (GeometryLinkDynamic *)(* foundPointToIter) );
		}
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

DynamicObjectsContructor & DynamicObjectsContructor::getInstance()
{
	static DynamicObjectsContructor instance;
	return instance;
}













