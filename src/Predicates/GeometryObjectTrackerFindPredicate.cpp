/*
 * GeometryObjectTrackerFindPredicate.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometryObjectTrackerFindPredicate.h"

GeometryObjectTrackerFindPredicate::GeometryObjectTrackerFindPredicate( GeometryMouseTrackingModes mode ) : m_Mode( mode )
{
}

GeometryObjectTrackerFindPredicate::~GeometryObjectTrackerFindPredicate()
{
}

bool GeometryObjectTrackerFindPredicate::operator()( const IGeometryObjectTracker * search ) const
{
	if( m_Mode == search->getType() )
	{
		return true;
	}
	return false;
}














