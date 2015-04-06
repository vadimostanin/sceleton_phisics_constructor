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
	cpSpaceStep( m_Space, (1.0/30.0) / 4.0 );
}

DynamicTimeLineManager & DynamicTimeLineManager::getInstance()
{
	static DynamicTimeLineManager instance;
	return instance;
}














