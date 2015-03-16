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

void GeometryObjectsManager::getPoints( vector<Point> & points )
{
	points.assign( m_Points.begin(), m_Points.end() );
}

bool GeometryObjectsManager::getPoint( int x, int y, Point & point )
{
	vector<Point>::iterator begin = m_Points.begin();
	vector<Point>::iterator end = m_Points.end();
	vector<Point>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		int point_x = (*iter).getX();
		int point_y = (*iter).getY();

		if( x > ( point_x + UN_TRACKING_POINT_RADIUS ) || x < ( point_x - UN_TRACKING_POINT_RADIUS ) ||
			y > ( point_y + UN_TRACKING_POINT_RADIUS ) || y < ( point_y - UN_TRACKING_POINT_RADIUS ) )
		{
			continue;
		}
		point = (*iter);
		return true;
	}
	return false;
}

GeometryObjectsManager & GeometryObjectsManager::getInstance()
{
	static GeometryObjectsManager instance;
	return instance;
}
