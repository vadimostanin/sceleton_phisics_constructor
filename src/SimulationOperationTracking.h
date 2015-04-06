/*
 * SimulationOperationTracking.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef SIMULATIONOPERATIONTRACKING_H_
#define SIMULATIONOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include "DrawingContent.h"
#include "GeometryLink.h"
#include <chipmunk/chipmunk.h>
#include <vector>
using namespace std;

class SimulationOperationTracking : public IGeometryObjectTracker
{
public:
	SimulationOperationTracking( DrawingContent & viewUpdater );
	virtual ~SimulationOperationTracking();

	GeometryMouseTrackingModes getType() const;

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

	void deleteObject( int x, int y );

private:

	void constructGraphicObjects( vector<IGraphicObject *> & graphicObjects );
	void constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject );

	DrawingContent & m_ViewUpdater;
	IGeometryObject * m_GeometryObjectTracking;

	cpBody 		 * m_MouseBody;
	cpBody 		 * m_TrackingBody;
	cpConstraint * m_MouseJoint;
	cpSpace 	 * m_Space;

};

#endif /* SIMULATIONOPERATIONTRACKING_H_ */
