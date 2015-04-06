/*
 * DynamicObjectsManager.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#include "DynamicObjectsManager.h"
#include "DynamicObjectFindPredicate.h"
#include <algorithm>

DynamicObjectsManager::DynamicObjectsManager()
{
}

DynamicObjectsManager::~DynamicObjectsManager()
{
}

void DynamicObjectsManager::addObject( IDynamicObject * object )
{
	m_dynamicObjects.push_back( object );
}

void DynamicObjectsManager::removeObject( IDynamicObject * object )
{
	DynamicObjectFindPredicate predicate( object );
	vector<IDynamicObject *>::iterator found_iter = std::find_if( m_dynamicObjects.begin(), m_dynamicObjects.end(), predicate );
	if( found_iter == m_dynamicObjects.end() )
	{
		return;
	}
	m_dynamicObjects.erase( found_iter );
	IDynamicObject * object_ptr = (* found_iter);
	delete object_ptr;
}

void DynamicObjectsManager::getObjects( vector<IDynamicObject *> & objects )
{
	objects = m_dynamicObjects;
}

void DynamicObjectsManager::setObjects( vector<IDynamicObject *> & objects )
{
	clearObjects();
	m_dynamicObjects = objects;
}

void DynamicObjectsManager::appendObjects( vector<IDynamicObject *> & objects )
{
	vector<IDynamicObject *>::iterator begin = objects.begin();
	vector<IDynamicObject *>::iterator end = objects.end();
	vector<IDynamicObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		m_dynamicObjects.push_back( (* iter) );
	}
}

void DynamicObjectsManager::clearObjects()
{
	vector<IDynamicObject *>::iterator begin = m_dynamicObjects.begin();
	vector<IDynamicObject *>::iterator end = m_dynamicObjects.end();
	vector<IDynamicObject *>::iterator iter = begin;
	for( ; iter != end ; iter++ )
	{
		IDynamicObject * object_ptr = (* iter);
		delete object_ptr;
	}
	m_dynamicObjects.clear();
}

DynamicObjectsManager & DynamicObjectsManager::getInstance()
{
	static DynamicObjectsManager instance;
	return instance;
}
















