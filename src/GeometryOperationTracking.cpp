/*
 * GeometryOperationTracking.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryOperationTracking.h"
#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GraphicPointHighlighted.h"

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

	size_t count = objects.size();

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
				break;
		}
		graphicObjects.push_back( graphicObject );
	}
}

void GeometryOperationTracking::trackerBegin( int x, int y )
{
	Point point;
	if( false == getPoint( x, y, point ) )
	{
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT ) );
		m_CurObjectState = OBJECT_POINT_CREATING;

		vector<IGraphicObject *> graphicObjects;

		constructGraphicObjects( graphicObjects );

		m_ViewUpdater.setGraphicObjects( graphicObjects );
	}
	else
	{
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK ) );

		vector<IGraphicObject *> graphicObjects;

		constructGraphicObjects( graphicObjects );

		m_ViewUpdater.setGraphicObjects( graphicObjects );

		m_CurObjectState = OBJECT_LINK_CREATING;
		/*
		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT ) );
		((Point*)m_GeometryObjectsTrackingStack[0])->setX( point.getX() );
		((Point*)m_GeometryObjectsTrackingStack[0])->setY( point.getY() );

		m_GeometryObjectsTrackingStack.push_back( GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK ) );
		((PointsLink*)m_GeometryObjectsTrackingStack[1])->setPointFrom( point );

		m_CurObjectState = OBJECT_LINK_CREATING;

//		m_ViewUpdater.highlightBegin( *((Point*)m_GeometryObjectsTrackingStack[0]) );
 */
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
				GeometryObjectsManager::getInstance().addObject( m_GeometryObjectsTrackingStack[0] );
			}
		}
//		m_ViewUpdater.highlightEnd();
	}
	else if( m_CurObjectState == OBJECT_LINK_CREATING )
	{
//		m_ViewUpdater.highlightEnd();
	}

	vector<IGraphicObject *> graphicObjects;

	constructGraphicObjects( graphicObjects );

	m_ViewUpdater.setGraphicObjects( graphicObjects );

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

























