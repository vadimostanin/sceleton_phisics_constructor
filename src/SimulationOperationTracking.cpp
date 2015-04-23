/*
 * SimulationOperationTracking.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include "GeometryObjectFactory.h"
#include "DynamicObjectFactory.h"
#include "GeometrySpring.h"
#include <iostream>

#include "SimulationOperationTracking.h"
using namespace std;

#define GRABBABLE_MASK_BIT (1<<31)
static cpShapeFilter GRAB_FILTER = {CP_NO_GROUP, GRABBABLE_MASK_BIT, GRABBABLE_MASK_BIT};

SimulationOperationTracking::SimulationOperationTracking( DrawingContent & viewUpdater ) : m_ViewUpdater( viewUpdater ), m_GeometryObjectTracking( NULL ),
		m_MouseBody( 0 ), m_TrackingBody( 0 ), m_MouseJoint( 0 ), m_Space( 0 )
{
	m_MouseBody = cpBodyNewKinematic();
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
	cpVect mousePoint = cpv( x, y );

	cpSpace * space = DynamicObjectFactory::getInstance().getInstance().getSpace();
	m_Space = space;

	cpShape * shape = cpSpacePointQueryNearest( m_Space, mousePoint, 100.0, GRAB_FILTER, 0 );

	if( 0 == shape )
	{
		return;
	}

	cpVect new_mouse_position = cpv( x, y );
	cpBodySetPosition( m_MouseBody, new_mouse_position );

	m_TrackingBody = cpShapeGetBody( shape );


	m_MouseJoint = cpPivotJointNew2( m_MouseBody, m_TrackingBody, cpvzero, cpvzero );
//	cpPinJointSetDist( m_MouseJoint, 0.0 );
//	cpFloat distance = cpPinJointGetDist( m_MouseJoint );
//	cout << "distance=" << distance << endl << flush;

	cpConstraintSetMaxForce( m_MouseJoint, INFINITY );
	cpConstraintSetMaxBias( m_MouseJoint, INFINITY );
	cpSpaceAddConstraint( m_Space, m_MouseJoint );
}

void SimulationOperationTracking::trackerContinue( int x, int y )
{
	cpVect new_mouse_position = cpv( x, y );

	cpVect old_body_position = cpBodyGetPosition( m_MouseBody );

	cpVect new_point = cpvlerp( old_body_position, new_mouse_position, 1.0f );
	cpBodySetVelocity( m_MouseBody, cpvmult( cpvsub( new_mouse_position, old_body_position ), 0.0f ) );
	cpBodySetPosition( m_MouseBody, new_point );
}

void SimulationOperationTracking::trackerEnd( int x, int y )
{
	if( 0 == m_MouseJoint )
	{
		return;
	}
	cpSpaceRemoveConstraint( m_Space, m_MouseJoint );
//	cpPinJointSetDist( m_MouseJoint, 0.0 );
	cpConstraintFree( m_MouseJoint );
	m_MouseJoint = 0;
}

void SimulationOperationTracking::deleteObject( int x, int y )
{
}
