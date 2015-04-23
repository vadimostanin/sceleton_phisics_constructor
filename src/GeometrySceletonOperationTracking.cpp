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
#include "GraphicObjectsContrucor.h"
#include "GeometryLinkAddCondition.h"
#include "MouseCoordinatesHolder.h"
#include "GeometryLinkGetAbsoluteAnglePredicate.h"
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
	vector<IGeometryObject *> geometryObjects;
	GeometryObjectsManager::getInstance().getObjects( geometryObjects );

	GraphicObjectsContrucor::getInstance().convert( geometryObjects, graphicObjects );
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
	GeometryLink * found_link_from;
	IGeometryObject * new_object = NULL;
	if( true == GeometryObjectsManager::getInstance().getLinkUnderPoint( x, y, &found_link_from ) )
	{
		GeometrySpring * spring_object = (GeometrySpring *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_SPRING );
		new_object = spring_object;
		m_GeometryObjectTracking = spring_object;
		spring_object->setLinkFrom( found_link_from );
		spring_object->setLinkTo( found_link_from );
		spring_object->setConstructingState( GEOMETRYOBJECTCONSTRUCTING_INPROGRESS );

		cout << "add spring from:" << found_link_from->getId() << "; to:" << found_link_from->getId() << endl << flush;

		GeometryObjectsManager::getInstance().addObject( spring_object );
	}
	else if( true == GeometryObjectsManager::getInstance().getPoint( x, y, point ) )
	{
		new_object = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
		m_GeometryObjectTracking = new_object;
		GeometryLink * link_object = (GeometryLink *)new_object;

		link_object->setPointFrom( point );
		link_object->setPointTo( point );

		cout << "add link from:" << link_object->getPointFrom()->getX() << "x" << link_object->getPointFrom()->getY() << "; to:" <<
				link_object->getPointTo()->getX() << "x" << link_object->getPointTo()->getY() << endl << flush;

		GeometryObjectsManager::getInstance().addObject( link_object );
	}
	else
	{
		new_object = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
		m_GeometryObjectTracking = new_object;

		GeometryPoint * point_object = (GeometryPoint *)new_object;

		GeometryObjectsManager::getInstance().addObject( point_object );
		point_object->setX( x );
		point_object->setY( y );
		cout << "add point:" << point_object->getX() << "x" << point_object->getY() << endl << flush;
	}

	MouseCoordinatesHolder::getInstance().setX( x );
	MouseCoordinatesHolder::getInstance().setY( y );

	IGraphicObject * graphicObject;

	constructGraphicObject( new_object, &graphicObject );

	m_ViewUpdater.addGraphicObject( graphicObject );
}

void GeometrySceletonOperationTracking::trackerContinue( int x, int y )
{
	if( 0 == m_GeometryObjectTracking )
	{
		return;
	}
	MouseCoordinatesHolder::getInstance().setX( x );
	MouseCoordinatesHolder::getInstance().setY( y );
	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_SPRING )
	{
		GeometrySpring & geoSpring = *((GeometrySpring*)m_GeometryObjectTracking);
		const GeometryLink * linkFrom = geoSpring.getLinkFrom();
		const GeometryLink * link_to = NULL;
		bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestneighbourLink( *linkFrom, x, y, link_to );
		if( foundNearestPoint == true )
		{
			if( geoSpring.getLinkTo() != link_to )
			{
				geoSpring.setLinkTo( link_to );
			}
		}
		geoSpring.setIsClosedPath( x, y );
	}
	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_LINK )
	{
		GeometryLink & geoLink = *((GeometryLink*)m_GeometryObjectTracking);
		const GeometryPoint * pointFrom = geoLink.getPointFrom();
		const GeometryPoint * point_to;
		bool foundNearestPoint = GeometryObjectsManager::getInstance().getNearestPoint( *pointFrom, x, y, point_to );
		if( foundNearestPoint == true )
		{
			if( geoLink.getPointTo() != point_to )
			{
				geoLink.setPointTo( point_to );
			}
		}
	}
	else if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_POINT )
	{
		GeometryPoint * stack_point = (GeometryPoint*)m_GeometryObjectTracking;
		stack_point->setX( x );
		stack_point->setY( y );
	}

	IGraphicObject * graphicObject;

	constructGraphicObject( m_GeometryObjectTracking, &graphicObject );

	m_ViewUpdater.changeGraphicObject( graphicObject );
}

void GeometrySceletonOperationTracking::trackerEnd( int x, int y )
{
	if( 0 == m_GeometryObjectTracking )
	{
		return;
	}

	bool changed = false;

	if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_SPRING )
	{
		GeometrySpring * geometrySpring = (GeometrySpring *)m_GeometryObjectTracking;
		geometrySpring->setConstructingState( GEOMETRYOBJECTCONSTRUCTING_COMPLETE );

		changed = true;
	}
	else if( m_GeometryObjectTracking->getType() == GEOMETRYOBJECT_LINK )
	{
		GeometryLink * geoLink = (GeometryLink*)m_GeometryObjectTracking;
		GeometryLinkAddCondition condition( geoLink );
		if( false == condition() )
		{
			GeometryObjectsManager::getInstance().removeObjectSmart( m_GeometryObjectTracking );
			clearTrackingStack();

			changed = true;
		}
	}
	if( true == changed )
	{
		vector<IGraphicObject *> graphicObjects;
		constructGraphicObjects( graphicObjects );
		m_ViewUpdater.setGraphicObjects( graphicObjects );
	}
	clearTrackingStack();
}

void GeometrySceletonOperationTracking::deleteObject( int x, int y )
{
	GeometryPoint * point;
	if( false == GeometryObjectsManager::getInstance().getPoint( x, y, point ) )
	{
		return;
	}

	GeometryObjectsManager::getInstance().removeObjectSmart( point );

	vector<IGraphicObject *> graphicObjects;
	constructGraphicObjects( graphicObjects );
	m_ViewUpdater.setGraphicObjects( graphicObjects );
}

void GeometrySceletonOperationTracking::clearTrackingStack()
{
	m_GeometryObjectTracking = 0;
}
