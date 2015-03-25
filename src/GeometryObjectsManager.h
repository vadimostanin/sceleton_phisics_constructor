/*
 * GeometryObjectsManager.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTSMANAGER_H_
#define GEOMETRYOBJECTSMANAGER_H_

#include "Point.h"
#include "GeometryLink.h"

#include <vector>
using namespace std;

class GeometryObjectsManager
{
public:
	GeometryObjectsManager();
	virtual ~GeometryObjectsManager();

	void addObject( IGeometryObject * object );
	void removeObject( IGeometryObject * object );
	void getObjects( vector<IGeometryObject *> & objects );
	bool getPoint( int x, int y, Point ** point );
	bool getNearestPoint( const Point & startPoint, int x, int y, Point & point );

	void save( string filename );

	static GeometryObjectsManager & getInstance();

private:

	vector<IGeometryObject *> m_geometryObjects;
};

#endif /* GEOMETRYOBJECTSMANAGER_H_ */
