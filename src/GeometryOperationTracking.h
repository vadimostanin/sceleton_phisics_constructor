/*
 * GeometryOperationTracking.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOPERATIONTRACKING_H_
#define GEOMETRYOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include "ObjectOperationStatus.h"
#include "IViewUpdatable.h"
#include "Point.h"

#include <vector>
using namespace std;

class GeometryOperationTracking : public IGeometryObjectTracker
{
public:
	GeometryOperationTracking( IViewUpdatable & viewUpdater );
	virtual ~GeometryOperationTracking();

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

private:


	void clearTrackingStack();

	bool getPoint( int x, int y, Point & point );

	vector<IGeometryObject *> m_GeometryObjectsTrackingStack;
	ObjectState m_CurObjectState;
	IViewUpdatable & m_ViewUpdater;
};

#endif /* GEOMETRYOPERATIONTRACKING_H_ */
