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
#include "DrawingContent.h"
#include "Point.h"

#include <vector>
using namespace std;

class GeometryOperationTracking : public IGeometryObjectTracker
{
public:
	GeometryOperationTracking( DrawingContent & viewUpdater );
	virtual ~GeometryOperationTracking();

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

	void deleteObject( int x, int y );

private:

	void clearTrackingStack();

	bool getPoint( int x, int y, Point ** point );

	void constructGraphicObjects( vector<IGraphicObject *> & graphicObjects );
	void constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject );

	DrawingContent & m_ViewUpdater;
	IGeometryObject * m_GeometryObjectTracking;
};

#endif /* GEOMETRYOPERATIONTRACKING_H_ */
