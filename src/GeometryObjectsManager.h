/*
 * GeometryObjectsManager.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTSMANAGER_H_
#define GEOMETRYOBJECTSMANAGER_H_

#include "Point.h"
#include "PointsLink.h"

#include <vector>
using namespace std;

class GeometryObjectsManager
{
public:
	GeometryObjectsManager();
	virtual ~GeometryObjectsManager();

	void addPoint( Point & point );
	void addObject( IGeometryObject * object );
	void getObjects( vector<IGeometryObject *> & objects );
	bool getPoint( int x, int y, Point & point );

	static GeometryObjectsManager & getInstance();

private:

	vector<IGeometryObject *> m_geometryObjects;

	vector<PointsLink> m_Links;
	vector<Point> m_Points;
};

#endif /* GEOMETRYOBJECTSMANAGER_H_ */
