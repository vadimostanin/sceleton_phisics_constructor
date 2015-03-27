/*
 * GeometrySpringOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometrySpringOperationTracking.h"

GeometrySpringOperationTracking::GeometrySpringOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater )
{
}

GeometrySpringOperationTracking::~GeometrySpringOperationTracking()
{
}

GeometryMouseTrackingModes GeometrySpringOperationTracking::getType() const
{
	return SPRING_MODE_E;
}

void GeometrySpringOperationTracking::trackerBegin( int x, int y )
{
}

void GeometrySpringOperationTracking::trackerContinue( int x, int y )
{
}

void GeometrySpringOperationTracking::trackerEnd( int x, int y )
{
}

void GeometrySpringOperationTracking::deleteObject( int x, int y )
{
}
