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
		IGraphicObject * graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( (*iter), m_ViewUpdater.getDrawingCanvas() );

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

void GeometryOperationTracking::constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject )
{
	*graphicObject = GeometryObjectFactory::getInstance().createGraphicObject( geometryObject, m_ViewUpdater.getDrawingCanvas() );

	switch( geometryObject->getType() )
	{
		case GEOMETRYOBJECT_POINT:
		{
//			int x = ((Point*)geometryObject)->getX();
//			int y = ((Point*)geometryObject)->getY();
//			((Point &)(* graphicObject )->getGeometryObject()).setX( x );
//			((Point &)(* graphicObject )->getGeometryObject()).setY( y );
		}
		break;
		case GEOMETRYOBJECT_POINT_HIGHLIGHTED:
		{
			((Point &)(* graphicObject )->getGeometryObject()).setX( ((Point*)geometryObject)->getX() );
			((Point &)(* graphicObject )->getGeometryObject()).setY( ((Point*)geometryObject)->getY() );
		}
		break;
		case GEOMETRYOBJECT_LINK:
		{
//			const Point & pointFrom = (( GeometryLink * )geometryObject)->getPointFrom();
//			const Point & pointTo =   (( GeometryLink * )geometryObject)->getPointTo();
//
//			((GeometryLink &)(* graphicObject )->getGeometryObject()).setPointFrom( pointFrom );
//			((GeometryLink &)(* graphicObject )->getGeometryObject()).setPointTo( pointTo );
		}
		break;
	}
}

void GeometryOperationTracking::trackerBegin( int x, int y )
{
	Point * point;
	IGeometryObject * new_object = NULL;
	if( false == getPoint( x, y, &point ) )
	{
		new_object = (Point *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
		m_GeometryObjectTracking = new_object;

		Point * point_object = (Point *)new_object;
       
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

	IGraphicObject * graphicObject;

	constructGraphicObject( new_object, &graphicObject );

	m_ViewUpdater.addGraphicObject( graphicObject );
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
		Point temp_point;
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
		Point * stack_point = (Point*)m_GeometryObjectTracking;
		stack_point->setX( x );
		stack_point->setY( y );
	}

	IGraphicObject * graphicObject;

	constructGraphicObject( m_GeometryObjectTracking, &graphicObject );

	m_ViewUpdater.changeGraphicObject( graphicObject );
}

void GeometryOperationTracking::trackerEnd( int x, int y )
{
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

	IGraphicObject * graphicObject;

	constructGraphicObject( point, &graphicObject );

	m_ViewUpdater.deleteGraphicObject( graphicObject );
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
