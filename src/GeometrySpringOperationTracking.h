/*
 * GeometrySpringOperationTracking.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYSPRINGOPERATIONTRACKING_H_
#define GEOMETRYSPRINGOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include <vector>
using namespace std;

class GeometrySpringOperationTracking : public IGeometryObjectTracker
{
public:
	GeometrySpringOperationTracking();
	virtual ~GeometrySpringOperationTracking();

	GeometryMouseTrackingModes getType() const;

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

	void deleteObject( int x, int y );
};

#endif /* GEOMETRYSPRINGOPERATIONTRACKING_H_ */
