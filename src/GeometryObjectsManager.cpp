/*
 * GeometryObjectsManager.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"

#define UN_TRACKING_POINT_RADIUS 40

GeometryObjectsManager::GeometryObjectsManager()
{
}

GeometryObjectsManager::~GeometryObjectsManager()
{
}

void GeometryObjectsManager::addPoint( Point & point )
{
	m_Points.push_back( point );
}

void GeometryObjectsManager::addObject( IGeometryObject * object )
{
	m_geometryObjects.push_back( object );
}

void GeometryObjectsManager::getObjects( vector<IGeometryObject *> & objects )
{
	objects = m_geometryObjects;
}

bool GeometryObjectsManager::getPoint( int x, int y, Point & point )
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		if( (*iter)->getType() != GEOMETRYOBJECT_POINT && (*iter)->getType() != GEOMETRYOBJECT_POINT_HIGHLIGHTED )
		{
			continue;
		}
		Point * point_iter = (Point *)(*iter);
		int point_x = point_iter->getX();
		int point_y = point_iter->getY();

		if( x > ( point_x + UN_TRACKING_POINT_RADIUS ) || x < ( point_x - UN_TRACKING_POINT_RADIUS ) ||
			y > ( point_y + UN_TRACKING_POINT_RADIUS ) || y < ( point_y - UN_TRACKING_POINT_RADIUS ) )
		{
			continue;
		}
		point = *point_iter;
		return true;
	}
	return false;
}

GeometryObjectsManager & GeometryObjectsManager::getInstance()
{
	static GeometryObjectsManager instance;
	return instance;
}
