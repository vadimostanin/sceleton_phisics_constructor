/*
 * GeometryObjectsManager.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: vostanin
 */

#include "GeometryObjectsManager.h"
#include "GeometryObjectFindPredicate.h"
#include "GeometryObjectFactory.h"
#include "GeometryLinksIsCrosslinkPredicate.h"
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

void GeometryObjectsManager::clearObjects()
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for(  ; iter != end ; iter++ )
	{
		IGeometryObject * object_ptr = (* iter);
		object_ptr->~IGeometryObject();
		GeometryObjectFactory::getInstance().deleteGeometryObject( object_ptr );
	}
	m_geometryObjects.clear();
}

void GeometryObjectsManager::removeObjectSmart( IGeometryObject * object )
{
	GeometryObjectFindPredicate predicate( object );
	vector<IGeometryObject *>::iterator found_iter = std::find_if( m_geometryObjects.begin(), m_geometryObjects.end(), predicate );
	if( found_iter == m_geometryObjects.end() )
	{
		return;
	}
    IGeometryObject * point_ptr = (* found_iter);

    point_ptr->~IGeometryObject();
    new(point_ptr) GeometryDummy;

    bool valid_all = true;
    do
    {
		vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
		vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
		vector<IGeometryObject *>::iterator iter = begin;
		for( ; iter != end ; iter++ )
		{
			IGeometryObject * object_ptr = (* iter);
			valid_all = object_ptr->isValid();
			if( false == valid_all )
			{
				object_ptr->~IGeometryObject();
				new( object_ptr ) GeometryDummy;
				valid_all = false;
				break;
			}
		}
    }while( false == valid_all );
    removeDummyObjects();
}

void GeometryObjectsManager::removeDummyObjects()
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for(  ; iter != end ;  )
	{
		IGeometryObject * object_ptr = (* iter);
		if( object_ptr->getType() == GEOMETRYOBJECT_DUMMY )
		{
			iter = m_geometryObjects.erase( iter );
			end = m_geometryObjects.end();
			object_ptr->~IGeometryObject();
			GeometryObjectFactory::getInstance().deleteGeometryObject( object_ptr );
		}
		else
		{
			iter++;
		}
	}
}

void GeometryObjectsManager::getObjects( vector<IGeometryObject *> & objects )
{
	objects = m_geometryObjects;
}

bool GeometryObjectsManager::getPoint( int x, int y, GeometryPoint *& point )
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		if( (*iter)->getType() != GEOMETRYOBJECT_POINT )
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
		point = point_iter;
		return true;
	}
	return false;
}

bool GeometryObjectsManager::getNearestPoint( const GeometryPoint & startPoint,  int x, int y, const GeometryPoint * & point )
{
	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;
	double min_distance = INT_MAX;

	bool found = false;

	for( ; iter != end ; iter++ )
	{
		if( (*iter)->getType() != GEOMETRYOBJECT_POINT )
		{
			continue;
		}

		const GeometryPoint * point_iter = (GeometryPoint *)(*iter);

		if( startPoint == *point_iter )
		{
			continue;
		}

		int point_iter_x = point_iter->getX();
		int point_iter_y = point_iter->getY();

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

bool GeometryObjectsManager::getNearestneighbourLink( const GeometryLink & startLink,  int x, int y, const GeometryLink * & resultLink )
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

		const GeometryLink * link_iter = (GeometryLink *)(*iter);

		if( startLink == *link_iter )
		{
			continue;
		}

		int link_iter_center_x = ( link_iter->getPointFrom()->getX() + link_iter->getPointTo()->getX() ) / 2;
		int link_iter_center_y = ( link_iter->getPointFrom()->getY() + link_iter->getPointTo()->getY() ) / 2;

		double distance = sqrt( ( link_iter_center_x - x )*( link_iter_center_x - x ) + ( link_iter_center_y - y )*( link_iter_center_y - y ) );

		GeometryLinksIsCrosslinkPredicate isCrosslink( &startLink, link_iter );
		bool isCross = isCrosslink();
//		cout << "IsCross=" << isCross << endl << flush;
		if( distance >= min_distance || false == isCross )
		{
			continue;
		}
		min_distance = distance;
		found = true;
		resultLink = link_iter;
	}
	if( found == true )
	{
		return true;
	}
	return false;
}

bool GeometryObjectsManager::getNearestLink( const GeometryLink & startLink,  int x, int y, const GeometryLink * & resultLink )
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

		const GeometryLink * link_iter = (GeometryLink *)(*iter);

		if( startLink == *link_iter )
		{
			continue;
		}

		int link_iter_center_x = ( link_iter->getPointFrom()->getX() + link_iter->getPointTo()->getX() ) / 2;
		int link_iter_center_y = ( link_iter->getPointFrom()->getY() + link_iter->getPointTo()->getY() ) / 2;

		double distance = sqrt( ( link_iter_center_x - x )*( link_iter_center_x - x ) + ( link_iter_center_y - y )*( link_iter_center_y - y ) );

		if( distance >= min_distance )
		{
			continue;
		}
		min_distance = distance;
		found = true;
		resultLink = link_iter;
	}
	if( found == true )
	{
		return true;
	}
	return false;
}

bool GeometryObjectsManager::getLinkUnderPoint( int x, int y, GeometryLink ** result_link )
{
	bool found = false;

	const unsigned int square_border = 3000;

	vector<IGeometryObject *>::iterator begin = m_geometryObjects.begin();
	vector<IGeometryObject *>::iterator end = m_geometryObjects.end();
	vector<IGeometryObject *>::iterator iter = begin;

	const int border = 0;

	for(  ; iter != end ; iter ++ )
	{
		if( (*iter)->getType() == GEOMETRYOBJECT_LINK )
		{
			const GeometryPoint * pointFrom = ((GeometryLink &)*(*iter)).getPointFrom();
			const GeometryPoint * pointTo = ((GeometryLink &)*(*iter)).getPointTo();

			int min_x = pointFrom->getX() <= pointTo->getX() ? pointFrom->getX() : pointTo->getX();
			int max_x = pointFrom->getX() > pointTo->getX() ? pointFrom->getX() : pointTo->getX();

			int min_y = pointFrom->getY() <= pointTo->getY() ? pointFrom->getY() : pointTo->getY();
			int max_y = pointFrom->getY() > pointTo->getY() ? pointFrom->getY() : pointTo->getY();

			if( x < ( min_x + border ) || x > ( max_x - border ) || y < ( min_y + border ) || y > ( max_y - border ) )
			{
				continue;
			}

//			int square_full = ( pointFrom->getX() - pointTo->getX() ) * ( pointFrom->getY() - pointTo->getY() );

			int square_1 = ( pointFrom->getX() - pointTo->getX() ) * ( y - pointTo->getY() );
			int square_2 = ( pointFrom->getY() - pointTo->getY() ) * ( x - pointTo->getX() );

			unsigned int square_diff = abs( square_1 - square_2 );
			if( square_diff < square_border )
			{
				*result_link = (GeometryLink *)(* iter);
				found = true;
				break;
			}
		}
	}

	return found;
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

void GeometryObjectsManager::initTestingState1()
{
	GeometryPoint * point_1 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_1->setX( 400 );
	point_1->setY( 400 );
	GeometryPoint * point_2 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_2->setX( 400 );
	point_2->setY( 200 );
	GeometryPoint * point_3 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_3->setX( 600 );
	point_3->setY( 200 );
	GeometryLink * link_1 = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
	link_1->setPointFrom( point_1 );
	link_1->setPointTo( point_2 );
	GeometryLink * link_2 = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
	link_2->setPointFrom( point_2 );
	link_2->setPointTo( point_3 );
	GeometrySpring * spring_1 = (GeometrySpring *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_SPRING );
	spring_1->setLinkFrom( link_1 );
	spring_1->setLinkTo( link_2 );

	addObject( point_1 );
	addObject( point_2 );
	addObject( point_3 );

	addObject( link_1 );
	addObject( link_2 );

	addObject( spring_1 );
}

void GeometryObjectsManager::initTestingState2()
{
	GeometryPoint * point_1 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_1->setX( 200 );
	point_1->setY( 200 );
	GeometryPoint * point_2 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_2->setX( 200 );
	point_2->setY( 100 );
	GeometryPoint * point_3 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_3->setX( 100 );
	point_3->setY( 250 );
	GeometryPoint * point_4 = (GeometryPoint *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_POINT );
	point_4->setX( 400 );
	point_4->setY( 210 );
	GeometryLink * link_1 = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
	link_1->setPointFrom( point_1 );
	link_1->setPointTo( point_2 );
	GeometryLink * link_2 = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
	link_2->setPointFrom( point_1 );
	link_2->setPointTo( point_3 );
	GeometryLink * link_3 = (GeometryLink *)GeometryObjectFactory::getInstance().createGeometryObject( GEOMETRYOBJECT_LINK );
	link_3->setPointFrom( point_1 );
	link_3->setPointTo( point_4 );

	addObject( point_1 );
	addObject( point_2 );
	addObject( point_3 );
	addObject( point_4 );

	addObject( link_1 );
	addObject( link_2 );
	addObject( link_3 );
}

GeometryObjectsManager & GeometryObjectsManager::getInstance()
{
	static GeometryObjectsManager instance;
	return instance;
}














