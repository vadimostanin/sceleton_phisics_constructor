/*
 * GeometryEditingOperationTracking.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYEDITINGOPERATIONTRACKING_H_
#define GEOMETRYEDITINGOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include "DrawingContent.h"
#include "GeometryLink.h"
#include <vector>
using namespace std;

class GeometryEditingOperationTracking : public IGeometryObjectTracker
{
public:
	GeometryEditingOperationTracking( DrawingContent & viewUpdater );
	virtual ~GeometryEditingOperationTracking();

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

};

#endif /* GEOMETRYEDITINGOPERATIONTRACKING_H_ */
