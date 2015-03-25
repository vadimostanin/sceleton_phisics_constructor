/*
 * GeometryOperationTracking.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GraphicLink.h"
#include "GraphicPointHighlighted.h"
#include <iostream>
using namespace std;

GeometryOperationTracking::GeometryOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( 0 )
{
}

GeometryOperationTracking::~GeometryOperationTracking()
{

}

void GeometryOperationTracking::constructGraphicObjects( vector<IGraphicObject *> & graphicObjects )
{
	vector<IGeometryObject *> objects;
	GeometryObjectsManager::getInstance().getObjects( objects );

	vector<IGeometryObject *>::iterator begin = objects.begin();
	vector<IGeometryObject *>::iterator end = objects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		IGraphicObject * graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( (*iter)->getType(), m_ViewUpdater.getDrawingCanvas() );

		switch( (*iter)->getType() )
		{
			case GEOMETRYOBJECT_POINT:
			{
					int x = ((Point*)(*iter))->getX();
					int y = ((Point*)(*iter))->getY();
					((GraphicPoint *)graphicObject)->setX( x );
					((GraphicPoint *)graphicObject)->setY( y );
			}
				break;
			case GEOMETRYOBJECT_POINT_HIGHLIGHTED:
			{
				((GraphicPointHighlighted *)graphicObject)->setX( ((Point*)(*iter))->getX() );
				((GraphicPointHighlighted *)graphicObject)->setY( ((Point*)(*iter))->getY() );
			}
				break;
			case GEOMETRYOBJECT_LINK:
			{
				const Point & pointFrom = (( GeometryLink * )( * iter ))->getPointFrom();
				const Point & pointTo = (( GeometryLink * )( * iter ))->getPointTo();

				((GeometryLink &)graphicObject->getGeometryObject()).setPointFrom( pointFrom );
				((GeometryLink &)graphicObject->getGeometryObject()).setPointTo( pointTo );
			}
				break;
		}
		graphicObjects.push_back( graphicObject );
	}
}

void GeometryOperationTracking::trackerBegin( int x, int y )
{
	Point * point;
	if( false == getPoint( x, y, &point ) )
	{
		Point * stack_point = (Point *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
		m_GeometryObjectTracking = stack_point;
       
		GeometryObjectsManager::getInstance().addObject( stack_point );
		stack_point->setX( x );
		stack_point->setY( y );
	    cout << "add point:" << stack_point->getX() << "x" << stack_point->getY() << endl << flush;
	}
	else
	{
		GeometryLink * stack_link = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
		m_GeometryObjectTracking = stack_link;
		stack_link->setPointFrom( *point );
		stack_link->setPointTo( *point );

		cout << "add link from:" << stack_link->getPointFrom().getX() << "x" << stack_link->getPointFrom().getY() << "; to:" <<
				stack_link->getPointTo().getX() << "x" << stack_link->getPointTo().getY() << endl << flush;

		GeometryObjectsManager::getInstance().addObject( stack_link );
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

void GeometryOperationTracking::trackerContinue( int x, int y )
{
	if( m_GeometryObjectTracking == 0 )
	{
		return;
	}
	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_LINK )
	{
		GeometryLink & geoLink = *((GeometryLink*)m_GeometryObjectTracking);
		const Point & pointFrom = geoLink.getPointFrom();
		Point temp_point( x, y );
		bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestPoint( pointFrom, x, y, temp_point );
		if( foundNearestPoint == true )
		{
			geoLink.setPointTo( temp_point );
		}
//		cout << "add link from:" << geoLink.getPointFrom().getX() << "x" << geoLink.getPointFrom().getY() << "; to:" <<
//				geoLink.getPointTo().getX() << "x" << geoLink.getPointTo().getY() << endl << flush;
	}
	else if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_POINT )
	{
		Point * stack_point = (Point*)m_GeometryObjectTracking;
		stack_point->setX( x );
		stack_point->setY( y );
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );

	m_ViewUpdater.update();
}

void GeometryOperationTracking::trackerEnd( int x, int y )
{
	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );

	clearTrackingStack();
}

void GeometryOperationTracking::deleteObject( int x, int y )
{
	Point * point;
	if( false == getPoint( x, y, &point ) )
	{
		return;
	}

	GeometryObjectsManager::getInstance().removeObject( point );

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

bool GeometryOperationTracking::getPoint( int x, int y, Point ** point )
{
	bool found = GeometryObjectsManager::getInstance().getPoint( x, y, point );
	return found;
}

void GeometryOperationTracking::clearTrackingStack()
{
	m_GeometryObjectTracking = 0;
}
