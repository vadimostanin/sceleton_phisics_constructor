/*
 * GeometryObjectsManager.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include <cmath>
#include <limits.h>
#include <iostream>
#include <algorithm>

#define UN_TRACKING_POINT_RADIUS 40

GeometryObjectFindPredicate::GeometryObjectFindPredicate( IGeometryObject * origin ) : m_Origin( origin )
{

}

bool GeometryObjectFindPredicate::operator()( IGeometryObject * object )
{
	if( object->getId() == m_Origin->getId() )
	{
		return true;
	}
	return false;
}

GeometryObjectsManager::GeometryObjectsManager()
{
}

GeometryObjectsManager::~GeometryObjectsManager()
{
}

void GeometryObjectsManager::addObject( IGeometryObject * object )
{
	m_geometryObjects.push_back( object );
}

void GeometryObjectsManager::removeObject( IGeometryObject * object )
{
	GeometryObjectFindPredicate predicate( object );
	vector<IGeometryObject *>::iterator found_iter = std::find_if( m_geometryObjects.begin(), m_geometryObjects.end(), predicate );
	if( found_iter == m_geometryObjects.end() )
	{
		return;
	}
//	size_t count = m_geometryObjects.size();
//	cout << "drawing object before count = " << count << endl << flush;
	m_geometryObjects.erase( found_iter );
//	count = m_geometryObjects.size();
//	cout << "drawing object after count = " << count << endl << flush;
}

void GeometryObjectsManager::getObjects( vector<IGeometryObject *> & objects )
{
	objects = m_geometryObjects;
}

bool GeometryObjectsManager::getPoint( int x, int y, Point ** point )
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
		*point = (Point *)(*point_iter).clone();
		return true;
	}
	return false;
}

bool GeometryObjectsManager::getNearestPoint( const Point & startPoint,  int x, int y, Point & point )
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	double min_distance = INT_MAX;

	bool found = false;

	for( ; iter != end ; iter++ )
	{
		if( (*iter)->getType() != GEOMETRYOBJECT_POINT && (*iter)->getType() != GEOMETRYOBJECT_POINT_HIGHLIGHTED )
		{
			continue;
		}

		const Point & point_iter = *(Point *)(*iter);

		if( startPoint == point_iter )
		{
			continue;
		}

		int point_x = point_iter.getX();
		int point_y = point_iter.getY();

		double distance = sqrt( ( point_x - x )*( point_x - x ) + ( point_y - y )*( point_y - y ) );

		if( distance >= min_distance )
		{
			continue;
		}
		min_distance = distance;
		found = true;
		point = point_iter;
	}
	if( found == true )
	{
		return true;
	}
	return false;
}

GeometryObjectsManager & GeometryObjectsManager::getInstance()
{
	static GeometryObjectsManager instance;
	return instance;
}
