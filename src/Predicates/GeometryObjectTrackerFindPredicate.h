/*
 * GeometryObjectTrackerFindPredicate.h
 *
 *  Created on: Mar 27, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTTRACKERFINDPREDICATE_H_
#define GEOMETRYOBJECTTRACKERFINDPREDICATE_H_

#include "IGeometryObjectTracker.h"

class GeometryObjectTrackerFindPredicate
{
public:
	GeometryObjectTrackerFindPredicate( GeometryMouseTrackingModes mode );
	virtual ~GeometryObjectTrackerFindPredicate();

	bool operator()( const IGeometryObjectTracker * search ) const;

private:

	GeometryMouseTrackingModes m_Mode;

};

#endif /* GEOMETRYOBJECTTRACKERFINDPREDICATE_H_ */
