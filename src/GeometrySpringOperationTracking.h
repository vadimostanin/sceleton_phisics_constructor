/*
 * GeometrySpringOperationTracking.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYSPRINGOPERATIONTRACKING_H_
#define GEOMETRYSPRINGOPERATIONTRACKING_H_

#include "IGeometryObjectTracker.h"
#include "DrawingContent.h"
#include "GeometryLink.h"
#include <vector>
using namespace std;

class GeometrySpringOperationTracking : public IGeometryObjectTracker
{
public:
	GeometrySpringOperationTracking( DrawingContent & viewUpdater );
	virtual ~GeometrySpringOperationTracking();

	GeometryMouseTrackingModes getType() const;

	void trackerBegin( int x, int y );
	void trackerContinue( int x, int y );
	void trackerEnd( int x, int y );

	void deleteObject( int x, int y );

	bool getLinkUnderPoint( int x, int y, GeometryLink ** result_link );
	void constructGraphicObject( IGeometryObject * geometryObject, IGraphicObject ** graphicObject );

private:

	DrawingContent & m_ViewUpdater;
	IGeometryObject * m_GeometryObjectTracking;

};

#endif /* GEOMETRYSPRINGOPERATIONTRACKING_H_ */
