/*
 * GeometrySceletonOperationTracking.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometrySceletonOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GraphicLink.h"
#include "GraphicPointHighlighted.h"
#include <iostream>
using namespace std;

GeometrySceletonOperationTracking::GeometrySceletonOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( 0 )
{

}

GeometrySceletonOperationTracking::~GeometrySceletonOperationTracking()
{

}

void GeometrySceletonOperationTracking::constructGraphicObjects( vector<IGraphicObject *> & graphicObjects )
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

void GeometrySceletonOperationTracking::constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject )
{
	*graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( geometryObject, m_ViewUpdater.getDrawingCanvas() );
}

GeometryMouseTrackingModes GeometrySceletonOperationTracking::getType() const
{
	return SCELETON_MODE_E;
}

void GeometrySceletonOperationTracking::trackerBegin( int x, int y )
{
	GeometryPoint * point;
	IGeometryObject * new_object = NULL;
	if( false == getPoint( x, y, &point ) )
	{
		new_object = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
		m_GeometryObjectTracking = new_object;

		GeometryPoint * point_object = (GeometryPoint *)new_object;
       
		GeometryObjectsManager::getInstance().addObject( point_object );
		point_object->setX( x );
		point_object->setY( y );
	    cout << "add point:" << point_object->getX() << "x" << point_object->getY() << endl << flush;
	}
	else
	{
		new_object = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
		m_GeometryObjectTracking = new_object;
		GeometryLink * link_object = (GeometryLink *)new_object;

		link_object->setPointFrom( *point );
		link_object->setPointTo( *point );

		cout << "add link from:" << link_object->getPointFrom().getX() << "x" << link_object->getPointFrom().getY() << "; to:" <<
				link_object->getPointTo().getX() << "x" << link_object->getPointTo().getY() << endl << flush;

		GeometryObjectsManager::getInstance().addObject( link_object );
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
//
//	IGraphicObject * graphicObject;
//
//	constructGraphicObject( new_object, &graphicObject );
//
//	m_ViewUpdater.addGraphicObject( graphicObject );
}

void GeometrySceletonOperationTracking::trackerContinue( int x, int y )
{
	if( m_GeometryObjectTracking == 0 )
	{
		return;
	}
	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_LINK )
	{
		GeometryLink & geoLink = *((GeometryLink*)m_GeometryObjectTracking);
		const GeometryPoint & pointFrom = geoLink.getPointFrom();
		GeometryPoint temp_point;
		bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestPoint( pointFrom, x, y, temp_point );
		if( foundNearestPoint == true )
		{
			if( geoLink.getPointTo() != temp_point )
			{
				geoLink.setPointTo( temp_point );
			}
		}
	}
	else if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_POINT )
	{
		GeometryPoint * stack_point = (GeometryPoint*)m_GeometryObjectTracking;
		stack_point->setX( x );
		stack_point->setY( y );
	}

//	IGraphicObject * graphicObject;
//
//	constructGraphicObject( m_GeometryObjectTracking, &graphicObject );
//
//	m_ViewUpdater.changeGraphicObject( graphicObject );

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

void GeometrySceletonOperationTracking::trackerEnd( int x, int y )
{
	clearTrackingStack();
}

void GeometrySceletonOperationTracking::deleteObject( int x, int y )
{
	GeometryPoint * point;
	if( false == getPoint( x, y, &point ) )
	{
		return;
	}

	GeometryObjectsManager::getInstance().removeObject( point );

	IGraphicObject * graphicObject;

	constructGraphicObject( point, &graphicObject );

	m_ViewUpdater.deleteGraphicObject( graphicObject );
}

bool GeometrySceletonOperationTracking::getPoint( int x, int y, GeometryPoint ** point )
{
	bool found = GeometryObjectsManager::getInstance().getPoint( x, y, point );
	return found;
}

void GeometrySceletonOperationTracking::clearTrackingStack()
{
	m_GeometryObjectTracking = 0;
}
