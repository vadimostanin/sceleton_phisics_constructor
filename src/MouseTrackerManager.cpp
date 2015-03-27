/*
 * MouseTrackerManager.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#include "MouseTrackerManager.h"
#include "GeometryObjectTrackerFindPredicate.h"
#include <algorithm>
using namespace std;

MouseTrackerManager::MouseTrackerManager() : m_MouseListener( NULL )
{
}

MouseTrackerManager::~MouseTrackerManager()
{
}

MouseTrackerManager & MouseTrackerManager::getInstance()
{
	static MouseTrackerManager instance;
	return instance;
}

void MouseTrackerManager::addTracker( IGeometryObjectTracker * tracker )
{
	m_Trackers.push_back( tracker );
}

void MouseTrackerManager::setMouseListener( MouseListener * mouseListener )
{
	m_MouseListener = mouseListener;
}

void MouseTrackerManager::setMouseListenerTrackerMode( GeometryMouseTrackingModes mode )
{
	if( NULL == m_MouseListener )
	{
		return;
	}

	IGeometryObjectTracker * currMouseTracker = m_MouseListener->getMouseTracker();
	if( NULL != currMouseTracker && mode == currMouseTracker->getType() )
	{
		return;
	}
	GeometryObjectTrackerFindPredicate predicate( mode );
	vector<IGeometryObjectTracker *>::iterator found = find_if( m_Trackers.begin(), m_Trackers.end(), predicate );

	if( found == m_Trackers.end() )
	{
		return;
	}

	m_MouseListener->setMouseTracker( (* found) );
}














