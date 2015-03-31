/*
 * GeometryEditingOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GeometrySpring.h"
#include <iostream>

#include "GeometryEditingOperationTracking.h"
using namespace std;

GeometryEditingOperationTracking::GeometryEditingOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( NULL )
{
}

GeometryEditingOperationTracking::~GeometryEditingOperationTracking()
{
}

GeometryMouseTrackingModes GeometryEditingOperationTracking::getType() const
{
	return EDITING_MODE_E;
}

void GeometryEditingOperationTracking::constructGraphicObjects( vector<IGraphicObject *> & graphicObjects )
{
	vector<IGeometryObject *> objects;
	GeometryObjectsManager::getInstance().getObjects( objects );

	vector<IGeometryObject *>::iterator begin = objects.begin();
	vector<IGeometryObject *>::iterator end = objects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		IGraphicObject * graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( (*iter), m_ViewUpdater.getDrawingCanvas() );

		graphicObjects.push_back( graphicObject );
	}
}

void GeometryEditingOperationTracking::constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject )
{
	*graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( geometryObject, m_ViewUpdater.getDrawingCanvas() );
}

void GeometryEditingOperationTracking::trackerBegin( int x, int y )
{
	GeometryPoint * point;
	if( true == GeometryObjectsManager::getInstance().getPoint( x, y, point ) )
	{
		m_GeometryObjectTracking = point;
		printf( "new_object=%p\n", m_GeometryObjectTracking ); fflush( stdout );
	}
}

void GeometryEditingOperationTracking::trackerContinue( int x, int y )
{
	if( m_GeometryObjectTracking == 0 )
	{
		return;
	}
	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_POINT )
	{
		GeometryPoint * stack_point = (GeometryPoint*)m_GeometryObjectTracking;
		stack_point->setX( x );
		stack_point->setY( y );
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

void GeometryEditingOperationTracking::trackerEnd( int x, int y )
{
	m_GeometryObjectTracking = 0;
}

void GeometryEditingOperationTracking::deleteObject( int x, int y )
{
}
