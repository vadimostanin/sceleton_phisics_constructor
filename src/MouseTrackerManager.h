/*
 * MouseTrackerManager.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef MOUSETRACKERMANAGER_H_
#define MOUSETRACKERMANAGER_H_

#include "IGeometryObjectTracker.h"
#include "GeometryMouseTrackingModes.h"
#include "IGeometryObjectTracker.h"
#include "MouseListener.h"
#include <vector>
using namespace std;

class MouseTrackerManager
{
	MouseTrackerManager();
	~MouseTrackerManager();
public:

	void addTracker( IGeometryObjectTracker * tracker );

	void setMouseListener( MouseListener * mouseListener );
	void setMouseListenerTrackerMode( GeometryMouseTrackingModes mode );

	static MouseTrackerManager & getInstance();

private:

	MouseListener * m_MouseListener;
	vector<IGeometryObjectTracker *> m_Trackers;
};

#endif /* MOUSETRACKERMANAGER_H_ */
