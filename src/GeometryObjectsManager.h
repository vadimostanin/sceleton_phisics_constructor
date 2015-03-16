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
	void getPoints( vector<Point> & points );
	bool getPoint( int x, int y, Point & point );

	void getLinks( vector<PointsLink> & links );

	static GeometryObjectsManager & getInstance();

private:

	vector<PointsLink> m_Links;
	vector<Point> m_Points;
};

#endif /* GEOMETRYOBJECTSMANAGER_H_ */
