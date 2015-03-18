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

GeometryOperationTracking::GeometryOperationTracking( DrawingContent & viewUpdater ) :
		m_CurObjectState( OBJECT_NONE ), m_ViewUpdater( viewUpdater )
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
		IGraphicObject * graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( (*iter)->getType() );

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
				((GraphicPointHighlighted *)graphicObject)->setX( ((Point*)(*iter))->getX() );
				((GraphicPointHighlighted *)graphicObject)->setY( ((Point*)(*iter))->getY() );
			break;
			case GEOMETRYOBJECT_LINK:
				((GraphicLink *)graphicObject)->setPointFrom( *(Point*)(*iter));
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
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT ) );
		m_CurObjectState = OBJECT_POINT_CREATING;
	}
	else
	{
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK ) );
		((PointsLink*)m_GeometryObjectsTrackingStack[0])->setPointFrom( *point );

		m_CurObjectState = OBJECT_LINK_CREATING;
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

void GeometryOperationTracking::trackerContinue( int x, int y )
{
	if( m_CurObjectState == OBJECT_NONE )
	{
		return;
	}
	else if( m_CurObjectState == OBJECT_LINK_CREATING )
	{
		if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_LINK )
		{
			PointsLink & geoLink = *((PointsLink*)m_GeometryObjectsTrackingStack[0]);
			const Point & pointFrom = geoLink.getPointFrom();
			Point temp_point( x, y );
			bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestPoint( pointFrom, x, y, temp_point );
			if( foundNearestPoint == true )
			{
				geoLink.setPointTo( temp_point );

				vector<IGraphicObject *> graphicObjects;

				constructGraphicObjects( graphicObjects );

				GraphicLink * graphLink = (GraphicLink *)GeometryObjectFactory::getInstance().createGraphicObject( GEOMETRYOBJECT_LINK );
				*graphLink = geoLink;

				graphicObjects.push_back( graphLink );

				m_ViewUpdater.setGraphicObjects( graphicObjects );
			}
		}
	}
	else if( m_CurObjectState == OBJECT_POINT_CREATING )
	{
		if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_POINT )
		{
			((Point*)m_GeometryObjectsTrackingStack[0])->setX( x );
			((Point*)m_GeometryObjectsTrackingStack[0])->setY( y );
		}
	}

	m_ViewUpdater.update();
}

void GeometryOperationTracking::trackerEnd( int x, int y )
{
	if( m_CurObjectState == OBJECT_POINT_CREATING )
	{
		if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_POINT )
		{
			Point * stack_point = ((Point*)m_GeometryObjectsTrackingStack[0]);
			stack_point->setX( x );
			stack_point->setY( y );

			Point * point;
			if( false == getPoint( x, y, &point ) )
			{
				GeometryObjectsManager::getInstance().addObject( stack_point );

				cout << "add point:" << stack_point->getX() << "x" << stack_point->getY() << endl << flush;
			}
		}
	}
	else if( m_CurObjectState == OBJECT_LINK_CREATING )
	{
		if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_LINK )
		{
			GraphicLink* link = ((GraphicLink*)m_GeometryObjectsTrackingStack[0]);

			cout << "add link from:" << link->getPointFrom().getX() << "x" << link->getPointFrom().getY() << "; to:" <<
					link->getPointTo().getX() << "x" << link->getPointTo().getY() << endl << flush;

			GeometryObjectsManager::getInstance().addObject( m_GeometryObjectsTrackingStack[0] );
		}
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );

	m_CurObjectState = OBJECT_NONE;

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
//	vector<IGeometryObject *>::iterator begin = m_GeometryObjectsTrackingStack.begin();
//	vector<IGeometryObject *>::iterator end = m_GeometryObjectsTrackingStack.end();
//	vector<IGeometryObject *>::iterator iter = begin;
//
//	for(  ; iter != end ; iter ++ )
//	{
//		delete (*iter);
//	}
	m_GeometryObjectsTrackingStack.clear();
}
