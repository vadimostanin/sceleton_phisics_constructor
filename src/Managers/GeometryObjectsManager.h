/*
 * GeometryObjectsManager.h
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTSMANAGER_H_
#define GEOMETRYOBJECTSMANAGER_H_

#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GeometrySpring.h"
#include "GeometryDummy.h"

#include <vector>
using namespace std;

class GeometryObjectsManager
{
	GeometryObjectsManager();
	virtual ~GeometryObjectsManager();

public:

	void addObject( IGeometryObject * object );
	void removeObjectSmart( IGeometryObject * object );
	void clearObjects();
	void getObjects( vector<IGeometryObject *> & objects );
	bool getPoint( int x, int y, GeometryPoint *& point );
	bool getNearestPoint( const GeometryPoint & startPoint, int x, int y, const GeometryPoint * & point );
	bool getNearestLink( const GeometryLink & startLink,  int x, int y, const GeometryLink * & link );
	bool getNearestneighbourLink( const GeometryLink & startLink,  int x, int y, const GeometryLink * & link );
	bool getLinkUnderPoint( int x, int y, GeometryLink ** result_link );

	void save( string filename );

	static GeometryObjectsManager & getInstance();

	void initTestingState1();
	void initTestingState2();

private:

	void removeDummyObjects();

	vector<IGeometryObject *> m_geometryObjects;
};

#endif /* GEOMETRYOBJECTSMANAGER_H_ */
