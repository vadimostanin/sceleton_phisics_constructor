/*
 * GeometryObjectBufferAllocator.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "GeometryObjectBufferAllocator.h"

#include "GeometryPoint.h"
#include "GeometryLink.h"
#include "GeometrySpring.h"
#include "GeometryDummy.h"

#include <malloc.h>

GeometryObjectBufferAllocator::GeometryObjectBufferAllocator()
{
	unsigned int maxSize = sizeof( GeometryPoint );
	if( maxSize < sizeof( GeometryLink ) )
	{
		maxSize = sizeof( GeometryLink );
	}
	if( maxSize < sizeof( GeometrySpring ) )
	{
		maxSize = sizeof( GeometrySpring );
	}
	if( maxSize < sizeof( GeometryDummy ) )
	{
		maxSize = sizeof( GeometryDummy );
	}
	m_allocBufferSize = maxSize;
}

GeometryObjectBufferAllocator::~GeometryObjectBufferAllocator()
{
}

void * GeometryObjectBufferAllocator::allocObjectBuffer()
{
	void * objectBuffer = calloc( 1, m_allocBufferSize );
	return objectBuffer;
}

void GeometryObjectBufferAllocator::deallocObjectBuffer( void * objectBufer )
{
	free( objectBufer );
}















