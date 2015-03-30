/*
 * GeometryObjectsManager.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include "GeometryObjectFindPredicate.h"
#include <cmath>
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <fstream>

#define UN_TRACKING_POINT_RADIUS 40

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
	m_geometryObjects.erase( found_iter );
}

void GeometryObjectsManager::getObjects( vector<IGeometryObject *> & objects )
{
	objects = m_geometryObjects;
}

bool GeometryObjectsManager::getPoint( int x, int y, GeometryPoint ** point )
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
		GeometryPoint * point_iter = (GeometryPoint *)(*iter);
		int point_x = point_iter->getX();
		int point_y = point_iter->getY();

		if( x > ( point_x + UN_TRACKING_POINT_RADIUS ) || x < ( point_x - UN_TRACKING_POINT_RADIUS ) ||
			y > ( point_y + UN_TRACKING_POINT_RADIUS ) || y < ( point_y - UN_TRACKING_POINT_RADIUS ) )
		{
			continue;
		}
		*point = (GeometryPoint *)(*point_iter).clone();
		return true;
	}
	return false;
}

bool GeometryObjectsManager::getNearestPoint( const GeometryPoint & startPoint,  int x, int y, GeometryPoint & point )
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

		const GeometryPoint & point_iter = *(GeometryPoint *)(*iter);

		if( startPoint == point_iter )
		{
			continue;
		}

		int point_iter_x = point_iter.getX();
		int point_iter_y = point_iter.getY();

		double distance = sqrt( ( point_iter_x - x )*( point_iter_x - x ) + ( point_iter_y - y )*( point_iter_y - y ) );

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

bool GeometryObjectsManager::getNearestLink( const GeometryLink & link_from,  int x, int y, GeometryLink & result_link )
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	double min_distance = INT_MAX;

	bool found = false;

	for( ; iter != end ; iter++ )
	{
		if( (*iter)->getType() != GEOMETRYOBJECT_LINK )
		{
			continue;
		}

		const GeometryLink & link_iter = *(GeometryLink *)(*iter);

		if( link_from == link_iter )
		{
			continue;
		}

		int link_iter_center_x = ( link_iter.getPointFrom().getX() + link_iter.getPointTo().getX() ) / 2;
		int link_iter_center_y = ( link_iter.getPointFrom().getY() + link_iter.getPointTo().getY() ) / 2;

		double distance = sqrt( ( link_iter_center_x - x )*( link_iter_center_x - x ) + ( link_iter_center_y - y )*( link_iter_center_y - y ) );

		if( distance >= min_distance )
		{
			continue;
		}
		min_distance = distance;
		found = true;
		result_link = link_iter;
	}
	if( found == true )
	{
		return true;
	}
	return false;
}

void GeometryObjectsManager::save( string filename )
{
	ofstream file( filename.c_str() );
	if( false == file.is_open() )
	{
		return;
	}

	vector<IGeometryObject *> objects;
	getObjects( objects );

	vector<IGeometryObject *>::iterator begin = objects.begin();
	vector<IGeometryObject *>::iterator end = objects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for(  ; iter != end ; iter ++ )
	{
		file << (*iter)->toString() << endl;
	}
}

GeometryObjectsManager & GeometryObjectsManager::getInstance()
{
	static GeometryObjectsManager instance;
	return instance;
}














