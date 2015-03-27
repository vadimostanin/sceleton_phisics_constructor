/*
 * IGeometryObjectTracker.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef IGEOMETRYOBJECTTRACKER_H_
#define IGEOMETRYOBJECTTRACKER_H_

#include "GeometryMouseTrackingModes.h"

class IGeometryObjectTracker
{
public:
	virtual ~IGeometryObjectTracker(){}

	virtual GeometryMouseTrackingModes getType() const = 0;

	virtual void trackerBegin( int x, int y ) = 0;
	virtual void trackerContinue( int x, int y ) = 0;
	virtual void trackerEnd( int x, int y ) = 0;

	virtual void deleteObject( int x, int y ) = 0;
};


#endif /* IGEOMETRYOBJECTTRACKER_H_ */
