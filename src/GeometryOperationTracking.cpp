/*
 * GeometryOperationTracking.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"

GeometryOperationTracking::GeometryOperationTracking( IViewUpdatable & viewUpdater ) :
		m_CurObjectState( OBJECT_NONE ), m_ViewUpdater( viewUpdater )
{
}

GeometryOperationTracking::~GeometryOperationTracking()
{

}

void GeometryOperationTracking::trackerBegin( int x, int y )
{
	Point point;
	if( false == getPoint( x, y, point ) )
	{
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT ) );
		m_CurObjectState = OBJECT_POINT_CREATING;
	}
	else
	{
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT ) );
		((Point*)m_GeometryObjectsTrackingStack[0])->setX( point.getX() );
		((Point*)m_GeometryObjectsTrackingStack[0])->setY( point.getY() );

		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK ) );
		((PointsLink*)m_GeometryObjectsTrackingStack[1])->setPointFrom( point );

		m_CurObjectState = OBJECT_LINK_CREATING;

		m_ViewUpdater.highlightBegin( *((Point*)m_GeometryObjectsTrackingStack[0]) );
	}
}

void GeometryOperationTracking::trackerContinue( int x, int y )
{
	if( m_CurObjectState == OBJECT_NONE )
	{
		return;
	}
	else if( m_CurObjectState == OBJECT_LINK_CREATING )
	{

	}
	if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_POINT )
	{
		((Point*)m_GeometryObjectsTrackingStack[0])->setX( x );
		((Point*)m_GeometryObjectsTrackingStack[0])->setY( y );
	}
}

void GeometryOperationTracking::trackerEnd( int x, int y )
{
	if( m_CurObjectState == OBJECT_POINT_CREATING )
	{
		if( m_GeometryObjectsTrackingStack[0]->getType() == GEOMETRYOBJECT_POINT )
		{
			((Point*)m_GeometryObjectsTrackingStack[0])->setX( x );
			((Point*)m_GeometryObjectsTrackingStack[0])->setY( y );

			Point point;
			if( false == getPoint( x, y, point ) )
			{
				GeometryObjectsManager::getInstance().addPoint( *((Point*)m_GeometryObjectsTrackingStack[0]) );
			}
		}
		m_ViewUpdater.highlightEnd();
	}
	else if( m_CurObjectState == OBJECT_LINK_CREATING )
	{
		m_ViewUpdater.highlightEnd();
	}

	m_ViewUpdater.update();

	m_CurObjectState = OBJECT_NONE;


	clearTrackingStack();
}

bool GeometryOperationTracking::getPoint( int x, int y, Point & point )
{
	bool found = GeometryObjectsManager::getInstance().getPoint( x, y, point );
	return found;
}

void GeometryOperationTracking::clearTrackingStack()
{
	vector<IGeometryObject *>::iterator begin = m_GeometryObjectsTrackingStack.begin();
	vector<IGeometryObject *>::iterator end = m_GeometryObjectsTrackingStack.end();
	vector<IGeometryObject *>::iterator iter = begin;

	for(  ; iter != end ; iter ++ )
	{
		delete (*iter);
	}
	m_GeometryObjectsTrackingStack.clear();
}

























