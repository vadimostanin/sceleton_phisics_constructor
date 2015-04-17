/*
 * GeometryObjectBufferAllocator.h
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#ifndef GEOMETRYOBJECTBUFFERALLOCATOR_H_
#define GEOMETRYOBJECTBUFFERALLOCATOR_H_

#include "GeometryObjectsTypes.h"

class GeometryObjectBufferAllocator
{
public:
	GeometryObjectBufferAllocator();
	virtual ~GeometryObjectBufferAllocator();


	void * allocObjectBuffer();
	void deallocObjectBuffer( void * objectBufer );

private:

	unsigned int m_allocBufferSize;

};

#endif /* GEOMETRYOBJECTBUFFERALLOCATOR_H_ */
