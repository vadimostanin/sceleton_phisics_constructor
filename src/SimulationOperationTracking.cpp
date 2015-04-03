/*
 * SimulationOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "GeometrySpring.h"
#include <iostream>

#include "SimulationOperationTracking.h"
using namespace std;

SimulationOperationTracking::SimulationOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( NULL )
{
}

SimulationOperationTracking::~SimulationOperationTracking()
{
}

GeometryMouseTrackingModes SimulationOperationTracking::getType() const
{
	return SIMULATION_MODE_E;
}

void SimulationOperationTracking::constructGraphicObjects( vector<IGraphicObject *> & graphicObjects )
{

}

void SimulationOperationTracking::trackerBegin( int x, int y )
{
	GeometryPoint * point;
	if( true == GeometryObjectsManager::getInstance().getPoint( x, y, point ) )
	{
		m_GeometryObjectTracking = point;
		printf( "new_object=%p\n", m_GeometryObjectTracking ); fflush( stdout );
	}

}

void SimulationOperationTracking::trackerContinue( int x, int y )
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

void SimulationOperationTracking::trackerEnd( int x, int y )
{
	m_GeometryObjectTracking = 0;
}

void SimulationOperationTracking::deleteObject( int x, int y )
{
}
