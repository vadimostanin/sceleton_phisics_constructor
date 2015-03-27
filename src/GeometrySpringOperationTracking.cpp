/*
 * GeometrySpringOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometrySpringOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryPoint.h"
#include "GeometryLink.h"
#include <iostream>
using namespace std;

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
	if( isLinkUnderPoint( x, y ) == true )
	{
		cout << "Found" << endl << flush;
	}
}

void GeometrySpringOperationTracking::trackerEnd( int x, int y )
{
}

void GeometrySpringOperationTracking::deleteObject( int x, int y )
{
}

bool GeometrySpringOperationTracking::isLinkUnderPoint( int x, int y )
{
	bool found = false;

	const unsigned int square_border = 1000;

	vector<IGeometryObject *> objects;
	GeometryObjectsManager::getInstance().getObjects( objects );

	vector<IGeometryObject *>::iterator begin = objects.begin();
	vector<IGeometryObject *>::iterator end = objects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		if( (*iter)->getType() == GEOMETRYOBJECT_LINK )
		{
			const GeometryPoint & pointFrom = ((GeometryLink &)*(*iter)).getPointFrom();
			const GeometryPoint & pointTo = ((GeometryLink &)*(*iter)).getPointTo();

			int square_1 = ( pointFrom.getX() - pointTo.getX() ) * ( y - pointTo.getY() );
			int square_2 = ( pointFrom.getY() - pointTo.getY() ) * ( x - pointTo.getX() );

			unsigned int square_diff = abs( square_1 - square_2 );
			if( square_diff < square_border )
			{
				found = true;
				break;
			}
		}
	}

	return found;
}
