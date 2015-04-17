/*
 * DynamicTimeLineManager.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: vostanin
 */

#include <DynamicTimeLineManager.h>

DynamicTimeLineManager::DynamicTimeLineManager() : m_Space( 0 )
{
}

DynamicTimeLineManager::~DynamicTimeLineManager()
{
}

void DynamicTimeLineManager::setSpace( cpSpace * space )
{
	m_Space = space;
}

void DynamicTimeLineManager::stepSpace()
{
	float timeStep = ( 1.0 / 30.0 ) / 12.0;
	cpSpaceStep( m_Space, timeStep );
	cpSpaceStep( m_Space, timeStep );
	cpSpaceStep( m_Space, timeStep );
	cpSpaceStep( m_Space, timeStep );
	cpSpaceStep( m_Space, timeStep );
	cpSpaceStep( m_Space, timeStep );
}

DynamicTimeLineManager & DynamicTimeLineManager::getInstance()
{
	static DynamicTimeLineManager instance;
	return instance;
}














