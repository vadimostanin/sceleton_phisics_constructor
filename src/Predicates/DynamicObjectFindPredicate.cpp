/*
 * DynamicObjectFindPredicate.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#include "DynamicObjectFindPredicate.h"

DynamicObjectFindPredicate::DynamicObjectFindPredicate( const IDynamicObject * object ) : m_OriginObject( object )
{
}

DynamicObjectFindPredicate::~DynamicObjectFindPredicate()
{
}

bool DynamicObjectFindPredicate::operator()( const  IDynamicObject * iterObject )
{
	if( m_OriginObject->getGeometryObject().getId() == iterObject->getGeometryObject().getId() )
	{
		return true;
	}
	return false;
}
















