/*
 * GeometrySpringOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometrySpringOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GeometrySpring.h"
#include <iostream>
using namespace std;

GeometrySpringOperationTracking::GeometrySpringOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( NULL )
{
}

GeometrySpringOperationTracking::~GeometrySpringOperationTracking()
{
}

GeometryMouseTrackingModes GeometrySpringOperationTracking::getType() const
{
	return SPRING_MODE_E;
}

void GeometrySpringOperationTracking::constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject )
{
	*graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( geometryObject, m_ViewUpdater.getDrawingCanvas() );
}

void GeometrySpringOperationTracking::trackerBegin( int x, int y )
{
	GeometryLink * found_link_from = NULL;
	if( getLinkUnderPoint( x, y, &found_link_from ) == false )
	{
		return;
	}

	GeometrySpring * spring_object = (GeometrySpring *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_SPRING );
	m_GeometryObjectTracking = spring_object;
	spring_object->setLinkFrom( *found_link_from );
	spring_object->setLinkTo( *found_link_from );

	IGraphicObject * graphicObject;

	constructGraphicObject( spring_object, &graphicObject );

	m_ViewUpdater.addGraphicObject( graphicObject );
}

void GeometrySpringOperationTracking::trackerContinue( int x, int y )
{
	if( m_GeometryObjectTracking == 0 )
	{
		return;
	}
	GeometryLink * found_link_from = NULL;
	if( getLinkUnderPoint( x, y, &found_link_from ) == true )
	{
		cout << "Found" << endl << flush;
	}

	GeometrySpring & geoSpring = *((GeometrySpring*)m_GeometryObjectTracking);
	const GeometryLink & linkFrom = geoSpring.getLinkFrom();
	GeometryLink temp_link;
	bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestLink( linkFrom, x, y, temp_link );
	if( foundNearestPoint == true )
	{
		if( geoSpring.getLinkTo() != temp_link )
		{
			geoSpring.setLinkTo( temp_link );
		}
	}

	IGraphicObject * graphicObject;

	constructGraphicObject( m_GeometryObjectTracking, &graphicObject );

	m_ViewUpdater.changeGraphicObject( graphicObject );
}

void GeometrySpringOperationTracking::trackerEnd( int x, int y )
{
}

void GeometrySpringOperationTracking::deleteObject( int x, int y )
{
}

bool GeometrySpringOperationTracking::getLinkUnderPoint( int x, int y, GeometryLink ** result_link )
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
				*result_link = (GeometryLink *)(* iter);
				found = true;
				break;
			}
		}
	}

	return found;
}
